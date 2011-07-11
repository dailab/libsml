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


#include <sml/sml_get_profile_pack_request.h>
#include <sml/sml_tree.h>
#include <sml/sml_boolean.h>
#include <sml/sml_time.h>
#include <stdio.h>



sml_get_profile_pack_request *sml_get_profile_pack_request_init(){
	  sml_get_profile_pack_request *msg = (sml_get_profile_pack_request *) malloc(sizeof(sml_get_profile_pack_request));
	  memset(msg, 0, sizeof(sml_get_profile_pack_request));
	  msg->parameter_tree_path = sml_tree_path_init();
	  return msg;
}

void sml_get_profile_pack_request_write(sml_get_profile_pack_request *msg, sml_buffer *buf) {
    
	sml_buf_set_type_and_length(buf, SML_TYPE_LIST, 9);
	sml_octet_string_write(msg->server_id, buf);
	sml_octet_string_write(msg->username, buf);
	sml_octet_string_write(msg->password, buf);
	sml_boolean_write(msg->with_rawdata, buf);
	sml_time_write(msg->begin_time, buf);
	sml_time_write(msg->end_time, buf);
	sml_tree_path_write(msg->parameter_tree_path, buf);
	
	printf("TODO: %s - some struct members aren't written", __FUNCTION__);
	sml_buf_optional_write(buf); // object_list
    sml_buf_optional_write(buf); // das_details
}


sml_get_profile_pack_request *sml_get_profile_pack_request_parse(sml_buffer *buf) {
	
	sml_get_profile_pack_request *msg = (sml_get_profile_pack_request *) malloc(sizeof(sml_get_profile_pack_request));
	memset(msg, 0, sizeof(sml_get_profile_pack_request));
	
	if (sml_buf_get_next_type(buf) != SML_TYPE_LIST) {
		buf->error = 1;
		goto error;
	}
	
	if (sml_buf_get_next_length(buf) != 9) {
		buf->error = 1;
		goto error;
	}
	
	printf("TODO:sml_get_profile_pack_request_parse -> not implemented yet");

/*	msg->client_id = sml_octet_string_parse(buf);
	if (sml_buf_has_errors(buf)) goto error;
	
	msg->server_id = sml_octet_string_parse(buf);
	if (sml_buf_has_errors(buf)) goto error;
	
	msg->list_name = sml_octet_string_parse(buf);
	if (sml_buf_has_errors(buf)) goto error;
	*/
	/*msg->act_sensor_time = SML_SKIP_OPTIONAL sml_time_parse(buf);
	if (sml_buf_has_errors(buf)) goto error;
    
	msg->val_list = sml_list_parse(buf);
	if (sml_buf_has_errors(buf)) goto error;
	
	msg->list_signature = sml_octet_string_parse(buf);
	if (sml_buf_has_errors(buf)) goto error;
    
	msg->act_gateway_time = SML_SKIP_OPTIONAL sml_time_parse(buf);
	if (sml_buf_has_errors(buf)) goto error;
	*/
	return msg;
	
  error:
	sml_get_profile_pack_request_free(msg);
	return 0;
    
}

void sml_get_profile_pack_request_free(sml_get_profile_pack_request *msg){
	 printf("NYI: %s\n", __FUNCTION__);
}


