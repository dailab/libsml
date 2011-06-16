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


#include <sml/sml_boolean.h>
#include <stdio.h>

sml_boolean sml_boolean_parse(sml_buffer *buf) {
    printf("NYI: %s\n", __FUNCTION__);
    return 0;
}

void sml_boolean_write(sml_boolean boolean, sml_buffer *buf) {
    sml_buf_set_type_and_length(buf, SML_TYPE_BOOLEAN, 1);
    if (boolean == SML_BOOLEAN_FALSE) {
        buf->buffer[buf->cursor] = SML_BOOLEAN_FALSE;
    }
    else {
        buf->buffer[buf->cursor] = SML_BOOLEAN_TRUE;
    }
    buf->cursor++;
}



