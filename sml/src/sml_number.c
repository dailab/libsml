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

u64 mc_sml_parse_number(sml_buffer *buf, unsigned char type, int max_size) {

	int l, i;
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
	
	// TODO: this doesn't work for integers (leading 1's)
	// mathias runge: -> fixed bug in sml_value_parse for SML_TYPE_INTEGER -> see comment in sml_value.cpp
	//					 maybe this one is fixed too?
	for (i = 0; i < l; i++) {
		n <<= 8;
		n |= mc_sml_buf_get_current_byte(buf);
		mc_sml_buf_update_read_bytes(buf, 1);
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
