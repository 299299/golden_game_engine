#pragma once


/*

    int
    main (void) {
      unsigned char *str = "brian the monkey and bradley the kinkajou are friends";
      char *enc = b64_encode(str, strlen(str));

      printf("%s\n", enc); // YnJpYW4gdGhlIG1vbmtleSBhbmQgYnJhZGxleSB0aGUga2lua2Fqb3UgYXJlIGZyaWVuZHM=

      char *dec = b64_decode(enc, strlen(enc));

      printf("%s\n", dec); // YnJpYW4gdGhlIG1vbmtleSBhbmQgYnJhZGxleSB0aGUga2lua2Fqb3UgYXJlIGZyaWVuZHM=
      return 0;
    }

*/

/**
 * Encode `unsigned char *' source with `size_t' size.
 * Returns a `char *' base64 encoded string.
 */

char *
b64_encode (const unsigned char *, size_t);

/**
 * Dencode `char *' source with `size_t' size.
 * Returns a `unsigned char *' base64 decoded string.
 */
unsigned char *
b64_decode (const char *, size_t);

/**
 * Dencode `char *' source with `size_t' size.
 * Returns a `unsigned char *' base64 decoded string + size of decoded string.
 */
unsigned char *
b64_decode_ex (const char *, size_t, size_t *);