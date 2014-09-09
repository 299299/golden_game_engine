#include <stdlib.h>
#include "jsmn.h"
#include "Prerequisites.h"

#ifdef JSMN_NEXT_LINKS
#   ifndef JSMN_PARENT_LINKS
#       error "Cannot parse without parent links"
#   endif
#endif


/**
 * Allocates a fresh unused token from the token pull.
 */
static jsmntok_t *jsmn_alloc_token(jsmn_parser *parser, jsmntok_t *tokens, size_t num_tokens) {
    jsmntok_t *tok;

#ifndef JSMN_HUGE_FILES
    // this assert will fail if you are trying to parse huge file without JSMN_HUGE_FILES define!
    HK_ASSERT2(0, parser->toknext + 1 < JSMN_INVALID_VALUE, "huge file toknext error!");
#endif
    
    tok = &tokens[parser->toknext++];
    tok->start = tok->end = JSMN_INVALID_VALUE;
    tok->size = 0;
    tok->is_key = 0;
#ifdef JSMN_PARENT_LINKS
    tok->parent = JSMN_INVALID_VALUE;
#endif
#ifdef JSMN_NEXT_LINKS
    tok->next = JSMN_INVALID_VALUE;
#endif
    return tok;
}

/**
 * Fills token type and boundaries.
 */
static void jsmn_fill_token(jsmntok_t *token, jsmntype_t type, 
                            unsigned int start, unsigned int end) {
    token->type = type;
    token->start = (jsmn_uint_t)start;
    token->end = (jsmn_uint_t)end;
    token->size = 0;
}

/**
 * Makes previous token of the same parent to point to this one
 */
static void jsmn_link_array_token(jsmn_parser *parser, jsmntok_t *tokens) {
#ifdef JSMN_NEXT_LINKS
    int i;

    if (tokens[parser->toksuper].type == JSMN_ARRAY) {
        for (i = parser->toknext - 2; i >= 0; --i) {
            if (tokens[i].parent == tokens[parser->toknext - 1].parent) {
                tokens[i].next = parser->toknext - 1;
                break;
            }
            else if (tokens[i].parent < tokens[parser->toknext - 1].parent)
                break;
        }
    }
#endif
}

static int jsmn_string_has_root(jsmn_parser *parser, const char *js) {
    for (; js[parser->pos] != '\0'; parser->pos++) {
        switch (js[parser->pos]) {
        case '{':
            return 1;

        case '\"':
            return 0;

        case '\t' : case '\r' : case '\n' : case ':' : case ',': case ' ': case '}': case ']':
            break;
        }
    }

    return 0;
}

/**
 * Fills next available token with JSON primitive.
 */
static jsmnerr_t jsmn_parse_primitive(jsmn_parser *parser, const char *js,
        jsmntok_t *tokens, size_t num_tokens) {
    jsmntok_t *token;
    jsmn_uint_t start;

    start = (jsmn_uint_t)parser->pos;

    for (; js[parser->pos] != '\0'; parser->pos++) {
        switch (js[parser->pos]) {
#ifndef JSMN_STRICT
            /* In strict mode primitive must be followed by "," or "}" or "]" */
            case ':':
#endif
            case '\t' : case '\r' : case '\n' : case ' ' :
            case ','  : case ']'  : case '}' :
                goto found;
        }
        const char* offset = js + parser->pos;
        char value = js[parser->pos];
        if (value < 32 || value >= 127) {
            parser->pos = start;
            return JSMN_ERROR_INVAL;
        }
    }
#ifdef JSMN_STRICT
    /* In strict mode primitive must be followed by a comma/object/array */
    parser->pos = start;
    return JSMN_ERROR_PART;
#endif

found:
    token = jsmn_alloc_token(parser, tokens, num_tokens);
    jsmn_fill_token(token, JSMN_PRIMITIVE, start, parser->pos);
#ifdef JSMN_PARENT_LINKS
    token->parent = parser->toksuper;
#endif
    parser->pos--;
    return JSMN_SUCCESS;
}

/**
 * Fills next token with JSON string.
 */
static jsmnerr_t jsmn_parse_string(jsmn_parser *parser, const char *js, jsmntok_t *tokens, size_t num_tokens) {
    jsmntok_t *token;

    unsigned int start = parser->pos;

    parser->pos++;

    /* Skip starting quote */
    for (; js[parser->pos] != '\0'; parser->pos++) {
        char c = js[parser->pos];

        /* Quote: end of string */
        if (c == '\"') {
            token = jsmn_alloc_token(parser, tokens, num_tokens);
            jsmn_fill_token(token, JSMN_STRING, start+1, parser->pos);
#ifdef JSMN_PARENT_LINKS
            token->parent = parser->toksuper;
#endif
            return JSMN_SUCCESS;
        }

        /* Backslash: Quoted symbol expected */
        if (c == '\\') {
            parser->pos++;
            switch (js[parser->pos]) {
                /* Allowed escaped symbols */
                case '\"': case '/' : case '\\' : case 'b' :
                case 'f' : case 'r' : case 'n'  : case 't' :
                    break;
                /* Allows escaped symbol \uXXXX */
                case 'u':
                    /* @TODO */
                    break;
                /* Unexpected symbol */
                default:
                    parser->pos = start;
                    return JSMN_ERROR_INVAL;
            }
        }
    }
    parser->pos = start;
    return JSMN_ERROR_PART;
}

/**
 * Preparse JSON string to get tokens count
 */
jsmnerr_t jsmn_pre_parse(jsmn_parser *parser, const char* js, unsigned strSize, unsigned int* result)
{
    jsmnerr_t r;
    jsmntok_t token;
    *result = 0;

    if (!jsmn_string_has_root(parser, js))
    {
        ++(*result);
    }

    for (; js[parser->pos] != '\0'; ++parser->pos) {
        if(parser->pos >= strSize)
            break;
        char c = js[parser->pos];

        switch (c) {
            case '{': case '[':
                ++(*result);
                break;

            case '\"':
                parser->toknext = 0;
                r = jsmn_parse_string(parser, js, &token, 1);
                if (r < 0) return r;
                ++(*result);
                break;

            case '\t' : case '\r' : case '\n' : case ':' : case ',': case ' ': case '}': case ']':
                break;
#ifdef JSMN_STRICT
                /* In strict mode primitives are: numbers and booleans */
            case '-': case '0': case '1' : case '2': case '3' : case '4':
            case '5': case '6': case '7' : case '8': case '9':
            case 't': case 'f': case 'n' :
#else
                /* In non-strict mode every unquoted value is a primitive */
            default:
#endif
                parser->toknext = 0;
                r = jsmn_parse_primitive(parser, js, &token, 1);
                if (r < 0) return r;
                ++(*result);
                break;

#ifdef JSMN_STRICT
                /* Unexpected char in strict mode */
            default:
                return JSMN_ERROR_INVAL;
#endif

        }
    }

    return JSMN_SUCCESS;
}

/**
 * Parse JSON string and fill tokens.
 */
jsmnerr_t jsmn_parse(jsmn_parser *parser, const char *js, unsigned strSize, jsmntok_t *tokens, unsigned int num_tokens) {
    jsmnerr_t r;
    int i;
    jsmntok_t *token;
    char expects_key_token = 1;
    char opened_array = 0;
    char opened_object = 0;
    
    const int has_root = jsmn_string_has_root(parser, js);

    if (!has_root)
    {
        token = jsmn_alloc_token(parser, tokens, num_tokens);
        token->type = JSMN_OBJECT;
        token->start = (jsmn_uint_t)parser->pos;
        parser->toksuper = parser->toknext - 1;
    }

    for (; js[parser->pos] != '\0'; ++parser->pos) {
        if(parser->pos >= strSize)
            break;

        char type;
        char c = js[parser->pos];

        switch (c) {
            case '{': 
                expects_key_token = 1;
                ++opened_object;
            case '[':
                token = jsmn_alloc_token(parser, tokens, num_tokens);
                if (parser->toksuper != JSMN_INVALID_VALUE) {
                    tokens[parser->toksuper].size++;
#ifdef JSMN_PARENT_LINKS
                    token->parent = parser->toksuper;
#endif
                }
                switch (c) {
                case '{':
                    token->type = JSMN_OBJECT;
                    break;

                default:
                    ++opened_array;
                    token->type = JSMN_ARRAY;
                    break;
                }

                if (parser->toksuper != JSMN_INVALID_VALUE)
                    jsmn_link_array_token(parser, tokens);

                token->start = (jsmn_uint_t)parser->pos;
                parser->toksuper = parser->toknext - 1;
                break;
            case ']':
                --opened_array;
            case '}':
                switch (c) {
                case '}':
                    type = JSMN_OBJECT;
                    --opened_object;
                    break;

                default:
                    type = JSMN_ARRAY;
                    break;
                }

#ifdef JSMN_PARENT_LINKS
                if (parser->toknext < 1) {
                    return JSMN_ERROR_INVAL;
                }
                token = &tokens[parser->toknext - 1];
                for (;;) {
                    if (token->start != JSMN_INVALID_VALUE && token->end == JSMN_INVALID_VALUE) {
                        if (token->type != type) {
                            return JSMN_ERROR_INVAL;
                        }
                        token->end = (jsmn_uint_t)parser->pos + 1;
                        parser->toksuper = token->parent;
                        break;
                    }
                    if (token->parent == JSMN_INVALID_VALUE) {
                        break;
                    }
                    token = &tokens[token->parent];
                }
#else
                for (i = parser->toknext - 1; i >= 0; i--) {
                    token = &tokens[i];
                    if (token->start != JSMN_INVALID_VALUE && token->end == JSMN_INVALID_VALUE) {
                        if (token->type != type) {
                            return JSMN_ERROR_INVAL;
                        }
                        parser->toksuper = JSMN_INVALID_VALUE;
                        token->end = parser->pos + 1;
                        break;
                    }
                }
                /* Error if unmatched closing bracket */
                if (i == -1) return JSMN_ERROR_INVAL;
                for (; i >= 0; i--) {
                    token = &tokens[i];
                    if (token->start != JSMN_INVALID_VALUE && token->end == JSMN_INVALID_VALUE) {
                        parser->toksuper = i;
                        break;
                    }
                }
#endif
                break;
            case '\"':
                r = jsmn_parse_string(parser, js, tokens, num_tokens);
                if (r < 0) return r;
                if (parser->toksuper != JSMN_INVALID_VALUE)
                    tokens[parser->toksuper].size++;

                if (expects_key_token && (parser->toksuper == JSMN_INVALID_VALUE || tokens[parser->toksuper].type != JSMN_ARRAY))
                    tokens[parser->toknext - 1].is_key = expects_key_token;
                
#ifdef JSMN_NEXT_LINKS
                if (parser->toksuper == JSMN_INVALID_VALUE || tokens[parser->toksuper].type == JSMN_OBJECT) {
                    if (tokens[parser->toknext - 1].is_key) {
                        for (i = parser->toknext - 2; i >= 0; --i) {
                            if (tokens[i].parent == tokens[parser->toknext - 1].parent) {
                                if (tokens[i].is_key) {
                                    tokens[i].next = parser->toknext - 1;
                                    break;
                                }
                            }
                            else if (tokens[i].parent < tokens[parser->toknext - 1].parent)
                                break;
                        }
                    }
                }
                else
                    jsmn_link_array_token(parser, tokens);
#endif
                break;
            case ',':
                expects_key_token = opened_object ? 1 : !opened_array;
                break;
            case ':' :
                expects_key_token = 0;
            case '\t' : case '\r' : case '\n' : case ' ': 
                break;
#ifdef JSMN_STRICT
            /* In strict mode primitives are: numbers and booleans */
            case '-': case '0': case '1' : case '2': case '3' : case '4':
            case '5': case '6': case '7' : case '8': case '9':
            case 't': case 'f': case 'n' :
#else
            /* In non-strict mode every unquoted value is a primitive */
            default:
#endif
                r = jsmn_parse_primitive(parser, js, tokens, num_tokens);
                if (r < 0) return r;
                if (parser->toksuper != JSMN_INVALID_VALUE) {
                    tokens[parser->toksuper].size++;

                    jsmn_link_array_token(parser, tokens);

                }
                break;

#ifdef JSMN_STRICT
            /* Unexpected char in strict mode */
            default:
                return JSMN_ERROR_INVAL;
#endif

        }
    }

    if (!has_root)
    {
        tokens[0].end = (jsmn_uint_t)parser->pos + 1;
    }

    if (opened_object || opened_array)
    {
        return JSMN_ERROR_PART;
    }

    return JSMN_SUCCESS;
}

/**
 * Creates a new parser based over a given  buffer with an array of tokens 
 * available.
 */
void jsmn_init(jsmn_parser *parser) {
    parser->pos = 0;
    parser->toknext = 0;
    parser->toksuper = JSMN_INVALID_VALUE;
}

