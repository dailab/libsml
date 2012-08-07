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


#include <sml/sml_number.h>
#include <string.h>
#include <stdio.h>

#define SML_BIG_ENDIAN 1
#define SML_LITTLE_ENDIAN 0

int sml_number_endian();
void sml_number_byte_swap(unsigned char *bytes, int bytes_len);

void *sml_number_init(u64 number, unsigned char type, int size) {
	
	unsigned char* bytes = (unsigned char*)&number;

	// Swap bytes of big-endian number so that
	// memcpy copies the right part
	if (sml_number_endian() == SML_BIG_ENDIAN) {
		  bytes += sizeof(u64) - size;
	}

	unsigned char *np = malloc(size);
	memset(np, 0, size);
	memcpy(np, bytes, size);
	return np;
}

void *sml_number_parse(sml_buffer *buf, unsigned char type, int max_size) {
	if (sml_buf_optional_is_skipped(buf)) {
		return 0;
	}

	int l, i;
	unsigned char b;
	short negative_int = 0;

	if (sml_buf_get_next_type(buf) != type) {
		buf->error = 1;
		return 0;
	}

	l = sml_buf_get_next_length(buf);
	if (l < 0 || l > max_size) {
		buf->error = 1;
		return 0;
	}

	unsigned char *np = malloc(max_size);
	memset(np, 0, max_size);

	b = sml_buf_get_current_byte(buf);
	if (type == SML_TYPE_INTEGER && (b & 128)) {
		negative_int = 1;
	}

	int missing_bytes = max_size - l;
	memcpy(&(np[missing_bytes]), sml_buf_get_current_buf(buf), l);

	if (negative_int) {
		for (i = 0; i < missing_bytes; i++) {
			np[i] = 0xFF;
		}
	}

	if (!(sml_number_endian() == SML_BIG_ENDIAN)) {
		sml_number_byte_swap(np, max_size);
	}
	sml_buf_update_bytes_read(buf, l);

	return np;
}

void sml_number_write(void *np, unsigned char type, int size, sml_buffer *buf) {
	if (np == 0) {
		sml_buf_optional_write(buf);
		return;
	}

	sml_buf_set_type_and_length(buf, type, size);
	memcpy(sml_buf_get_current_buf(buf), np, size);

	if (!(sml_number_endian() == SML_BIG_ENDIAN)) {
		sml_number_byte_swap(sml_buf_get_current_buf(buf), size);
	}

	sml_buf_update_bytes_read(buf, size);
}

void sml_number_byte_swap(unsigned char *bytes, int bytes_len) {
	int i;
	unsigned char ob[bytes_len];
	memcpy(&ob, bytes, bytes_len);
	
	for (i = 0; i < bytes_len; i++) {
		bytes[i] = ob[bytes_len - (i + 1)];
	}
}

int sml_number_endian() {
	int i = 1;
	char *p = (char *)&i;

	if (p[0] == 1)
		return SML_LITTLE_ENDIAN;
	else
		return SML_BIG_ENDIAN;
}

void sml_number_free(void *np) {
	if (np) {
		free(np);
	}
}

