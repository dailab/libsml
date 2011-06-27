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


#include <sml/sml_status.h>
#include <sml/sml_shared.h>

sml_status *sml_status_parse(sml_buffer *buf) {
	int type = sml_buf_get_next_type(buf);
	unsigned char byte = sml_buf_get_current_byte(buf);
	
	sml_status *state = (sml_status *) malloc(sizeof(sml_status));
	switch (type) {
		case SML_TYPE_UNSIGNED:
			switch (byte & SML_LENGTH_FIELD) {
				case SML_TYPE_NUMBER_8:
					state->status8 = sml_u8_parse(buf);
					break;
				case SML_TYPE_NUMBER_16:
					state->status16 = sml_u16_parse(buf);
					break;
				case SML_TYPE_NUMBER_16 + 1:
				case SML_TYPE_NUMBER_32:
					state->status32 = sml_u32_parse(buf);
					break;
				case SML_TYPE_NUMBER_32 + 1:
				case SML_TYPE_NUMBER_32 + 2:
				case SML_TYPE_NUMBER_32 + 3:
				case SML_TYPE_NUMBER_64:
					state->status64 = sml_u64_parse(buf);
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
	if (sml_buf_has_errors(buf)) {
		sml_status_free(state);
		return 0;
	}
	
	return state;
}

void sml_status_free(sml_status *status) {
    if (status) {
        free(status);
    }
}
