// Copyright 2011 Juri Glass, Mathias Runge, Nadim El Sayed 
// DAI-Labor, TU-Berlin
// 
// This file is part of libSML.
// 
// libSML is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// libSML is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with libSML.  If not, see <http://www.gnu.org/licenses/>.

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

