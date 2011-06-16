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


#include <sml/sml_get_list_request.h>
#include <stdio.h>

sml_get_list_request* sml_get_list_request_init(){
	  sml_get_list_request *msg = (sml_get_list_request *) malloc(sizeof(sml_get_list_request));
	  memset(msg, 0, sizeof(sml_get_list_request));

	  return msg;
}

void sml_get_list_request_write(sml_get_list_request *msg, sml_buffer *buf) {
    mc_sml_set_type_and_length(buf, SML_TYPE_LIST, 5);

    sml_octet_string_write(msg->client_id, buf);

    // optional server_id
    if (msg->server_id != NULL){
    	sml_octet_string_write(msg->server_id, buf);
    } else mc_sml_optional_write(buf);

    // optional username
    if (msg->username != NULL){
    	sml_octet_string_write(msg->username, buf);
    } else mc_sml_optional_write(buf);

    // optional password
    if (msg->password != NULL){
    	sml_octet_string_write(msg->password, buf);
    } else mc_sml_optional_write(buf);

    // optional list_name
    if (msg->list_name != NULL){
      sml_octet_string_write(msg->list_name,buf);
    } else  mc_sml_optional_write(buf);

}


sml_get_list_request *sml_get_list_request_parse(sml_buffer *buf) {
	
	sml_get_list_request *msg = (sml_get_list_request *) malloc(sizeof(sml_get_list_request));
	memset(msg, 0, sizeof(sml_get_list_request));
	
	if (mc_sml_buf_get_current_type(buf) != SML_TYPE_LIST) {
		buf->error = 1;
		goto error;
	}
	
	if (mc_sml_get_length(buf) != 5) {
		buf->error = 1;
		goto error;
	}
	
	msg->client_id = SML_SKIP_OPTIONAL sml_octet_string_parse(buf);
		if (mc_sml_buf_has_errors(buf)) goto error;
	
	msg->server_id = sml_octet_string_parse(buf);
		if (mc_sml_buf_has_errors(buf)) goto error;

	msg->username = SML_SKIP_OPTIONAL sml_octet_string_parse(buf);
		if (mc_sml_buf_has_errors(buf)) goto error;
	
	msg->password = SML_SKIP_OPTIONAL sml_octet_string_parse(buf);
		if (mc_sml_buf_has_errors(buf)) goto error;

	msg->list_name = SML_SKIP_OPTIONAL sml_octet_string_parse(buf);
		if (mc_sml_buf_has_errors(buf)) goto error;

	return msg;
	
error: 
	free(msg);
	return 0;
    
}


void sml_get_list_request_free(sml_get_list_request *msg) {
    if (msg) {
        sml_octet_string_free(msg->client_id);
        sml_octet_string_free(msg->server_id);
        sml_octet_string_free(msg->list_name);
        sml_octet_string_free(msg->username);
        sml_octet_string_free(msg->password);
        free(msg);
    }
}
