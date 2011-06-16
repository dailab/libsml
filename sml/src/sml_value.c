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


#include <sml/sml_value.h>

#include <stdio.h>

sml_value *sml_value_parse(sml_buffer *buf) {
	int type = mc_sml_buf_get_current_type(buf);
	unsigned char byte = mc_sml_buf_get_current_byte(buf);
	
	sml_value *value = (sml_value *) malloc(sizeof(sml_value));
    value->type = type;

	switch (type) {
		case SML_TYPE_OCTET_STRING:
			value->data.bytes = sml_octet_string_parse(buf);
			break;
		case SML_TYPE_UNSIGNED:
			switch (byte & SML_LENGTH_FIELD) {
				case SML_TYPE_NUMBER_8:
					value->data.uint8 = mc_sml_parse_u8(buf);
                    value->type |= SML_TYPE_NUMBER_8;
					break;
				case SML_TYPE_NUMBER_16:
					value->data.uint16 = mc_sml_parse_u16(buf);
                    value->type |= SML_TYPE_NUMBER_16;
					break;
				case SML_TYPE_NUMBER_16 + 1:
				case SML_TYPE_NUMBER_32:
					value->data.uint32 = mc_sml_parse_u32(buf);
                    value->type |= SML_TYPE_NUMBER_32;
					break;
				case SML_TYPE_NUMBER_32 + 1:
				case SML_TYPE_NUMBER_32 + 2:
				case SML_TYPE_NUMBER_32 + 3:
				case SML_TYPE_NUMBER_64:
					value->data.uint64 = mc_sml_parse_u64(buf);
                    value->type |= SML_TYPE_NUMBER_64;
					break;
				default:
					buf->error = 1;
					break;
			}
			break;

		case SML_TYPE_INTEGER:
			//switch (byte & SML_LENGTH_FIELD) {
			// Integer 59 00 00 00 00 00 01 20 09 could'nt be evaluated cause (byte & SML_LENGTH_FIELD)=9
			// but 8 is maximum :( -> now it's working
			// TODO: check if same problem exists for other SML_TYPEs too
			switch ((byte & SML_LENGTH_FIELD)-1) {
				case SML_TYPE_NUMBER_8:
					value->data.int8 = mc_sml_parse_i8(buf);
                    value->type |= SML_TYPE_NUMBER_8;
					break;
				case SML_TYPE_NUMBER_16:
					value->data.int16 = mc_sml_parse_i16(buf);
                    value->type |= SML_TYPE_NUMBER_16;
					break;
				case SML_TYPE_NUMBER_16 + 1:
				case SML_TYPE_NUMBER_32:
					value->data.int32 = mc_sml_parse_i32(buf);
                    value->type |= SML_TYPE_NUMBER_32;
					break;
				case SML_TYPE_NUMBER_32 + 1:
				case SML_TYPE_NUMBER_32 + 2:
				case SML_TYPE_NUMBER_32 + 3:
				case SML_TYPE_NUMBER_64:
					value->data.int64 = mc_sml_parse_i64(buf);
                    value->type |= SML_TYPE_NUMBER_64;
					break;
				default:
					buf->error = 1;
					break;
			}
			break;
		default:
			buf->error = 1;
			break;
	}
	if (mc_sml_buf_has_errors(buf)) {
		free(value);
		return 0;
	}
	
	return value;
}

void sml_value_write(sml_value *value, sml_buffer *buf) {
    if (value->type == SML_TYPE_BOOLEAN) {
        sml_boolean_write(value->data.boolean, buf);
    }
}

sml_value *sml_value_init() {
    sml_value *value = (sml_value *) malloc(sizeof(sml_value));
    memset(value, 0, sizeof(value));
    return value;
}

void sml_value_free(sml_value *value) {
    if (value) {
        if (value->type == SML_TYPE_OCTET_STRING) {
            sml_octet_string_free(value->data.bytes);
        }
        free(value);
    }
}

