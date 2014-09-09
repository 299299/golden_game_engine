#pragma once

#define JSMN_PARENT_LINKS
#define JSMN_NEXT_LINKS

//#define JSMN_HUGE_FILES


#ifdef JSMN_HUGE_FILES
    typedef unsigned int    jsmn_uint_t;
    typedef int             jsmn_int_t;
#else
    typedef unsigned short  jsmn_uint_t;
    typedef short           jsmn_int_t;
#endif


#define JSMN_INVALID_VALUE (jsmn_uint_t)-1


/**
 * JSON type identifier. Basic types are:
 *  o Object
 *  o Array
 *  o String
 *  o Other primitive: number, boolean (true/false) or null
 */
typedef enum {
    JSMN_PRIMITIVE = 0,
    JSMN_OBJECT = 1,
    JSMN_ARRAY = 2,
    JSMN_STRING = 3
} jsmntype_t;

typedef enum {
    /* Not enough tokens were provided */
    JSMN_ERROR_NOMEM = -1,
    /* Invalid character inside JSON string */
    JSMN_ERROR_INVAL = -2,
    /* The string is not a full JSON packet, more bytes expected */
    JSMN_ERROR_PART = -3,
    /* Everything was fine */
    JSMN_SUCCESS = 0
} jsmnerr_t;

/**
 * JSON token description.
 * @param       type    type (object, array, string etc.)
 * @param       start   start position in JSON data string
 * @param       end     end position in JSON data string
 * @param       is_key  indicates whether this token is key token (the one, that precedes ':' symbol)
 */
struct jsmntok {
    jsmn_uint_t start;
    jsmn_uint_t end;
    jsmn_uint_t size;
#ifdef JSMN_PARENT_LINKS
    jsmn_uint_t parent;
#endif
#ifdef JSMN_NEXT_LINKS
    jsmn_uint_t next;
#endif
    char type;
    char is_key;
};

typedef struct jsmntok jsmntok_t;

/**
 * JSON parser. Contains an array of token blocks available. Also stores
 * the string being parsed now and current position in that string
 */
typedef struct {
    unsigned int pos; /* offset in the JSON string */
    jsmn_uint_t toknext; /* next token to allocate */
    jsmn_uint_t toksuper; /* superior token node, e.g parent object or array */
} jsmn_parser;


#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create JSON parser over an array of tokens
 */
void jsmn_init(jsmn_parser *parser);

/**
 * Preparse JSON string to get tokens count. Does not validates data correctness
 */
jsmnerr_t jsmn_pre_parse(jsmn_parser *parser, const char* js, unsigned strSize, unsigned int* result);

/**
 * Run JSON parser. It parses a JSON data string into and array of tokens, each describing
 * a single JSON object.
 */
jsmnerr_t jsmn_parse(jsmn_parser *parser, const char *js, unsigned strSize, jsmntok_t *tokens, unsigned int num_tokens);

#ifdef __cplusplus
}
#endif
