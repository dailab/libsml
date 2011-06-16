#ifndef _SML_OCTET_STRING_H
#define	_SML_OCTET_STRING_H

#include <string.h>
#include "sml_shared.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
	unsigned char *str;
	int len;
} octet_string;

// sml signature
typedef octet_string sml_signature;

octet_string *sml_octet_string_init(unsigned char *str, int length);

octet_string *sml_octet_string_init_from_hex(char *str);

void sml_octet_string_free(octet_string *str);

// Parses a octet string, updates the buffer accordingly, memory must be free'd elsewhere.
octet_string *sml_octet_string_parse(sml_buffer *buf);

void sml_octet_string_write(octet_string *str, sml_buffer *buf);

int sml_octet_string_cmp_with_hex(octet_string *str, char *hex);

octet_string *sml_octet_string_generate_uuid();

#ifdef __cplusplus
}
#endif


#endif

