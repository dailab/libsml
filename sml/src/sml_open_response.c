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


#include <sml/sml_open_response.h>

#include <sml/sml_number.h>

sml_open_response *sml_open_response_parse(sml_buffer *buf) {
	sml_open_response *msg = (sml_open_response *) malloc(sizeof(sml_open_response));
	memset(msg, 0, sizeof(sml_open_response));
	
	if (sml_buf_get_next_type(buf) != SML_TYPE_LIST) {
		buf->error = 1;
		goto error;
	}
	
	if (sml_buf_get_next_length(buf) != 6) {
		buf->error = 1;
		goto error;
	}
	
	msg->codepage = sml_octet_string_parse(buf);
	if (sml_buf_has_errors(buf)) goto error;
	
	msg->client_id = sml_octet_string_parse(buf);
	if (sml_buf_has_errors(buf)) goto error;
	
	msg->req_file_id = sml_octet_string_parse(buf);
	if (sml_buf_has_errors(buf)) goto error;
	
	msg->server_id = sml_octet_string_parse(buf);
	if (sml_buf_has_errors(buf)) goto error;
	
	msg->ref_time = SML_SKIP_OPTIONAL sml_time_parse(buf);
	if (sml_buf_has_errors(buf)) goto error;
	
	msg->sml_version = sml_u8_parse(buf);
	if (sml_buf_has_errors(buf)) goto error;
	
	return msg;
error:
	sml_open_response_free(msg);
	return 0;
}

void sml_open_response_free(sml_open_response *msg) {
    if (msg) {
        sml_octet_string_free(msg->codepage);
        sml_octet_string_free(msg->client_id);
        sml_octet_string_free(msg->req_file_id);
        sml_octet_string_free(msg->server_id);
        sml_time_free(msg->ref_time);
		sml_number_free(msg->sml_version);
        free(msg);
    }
}
