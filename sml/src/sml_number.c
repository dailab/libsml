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

u64 sml_number_parse(sml_buffer *buf, unsigned char type, int max_size) {
	int l, i;
	unsigned char b;
	u64 n = 0;
	if (sml_buf_get_next_type(buf) != type) {
		buf->error = 1;
		return 0;
	}
	
	l = sml_buf_get_next_length(buf);
	if (l < 0 || l > max_size) {
		buf->error = 1;
		return 0;
	}
	
	b = sml_buf_get_current_byte(buf);
	// negative value with leading 1's
	if (type == SML_TYPE_INTEGER && b & 128) {
		n =~ n;
		b = 0xFF;
		for (i = 0; i < l; i++) {
			n <<= 8;
			n |= b;
			n = (n & ~b) | sml_buf_get_current_byte(buf);
			sml_buf_update_bytes_read(buf, 1);
		}
	}
	else {
		for (i = 0; i < l; i++) {
			n <<= 8;
			n |= sml_buf_get_current_byte(buf);
			sml_buf_update_bytes_read(buf, 1);
		}
	}
	return n;
}

void sml_number_write(unsigned char type, int size, u64 value, sml_buffer *buf) {
    sml_buf_set_type_and_length(buf, type, size);
    int i;
    u64 mask = 0xFF;
    mask <<= (8 * (size - 1));
    
    for (i = 0; i < size; i++) {
        buf->buffer[buf->cursor + i] = (unsigned char) ((mask & value) >> (8 * (size - i - 1)));
        mask >>= 8;
    }
    buf->cursor += size;
}
