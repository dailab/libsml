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


#include <sml/sml_open_request.h>

#include <sml/sml_number.h>
#include <stdio.h>


sml_open_request *sml_open_request_init(){
	sml_open_request *open_request = (sml_open_request *) malloc(sizeof(sml_open_request));
	memset(open_request, 0, sizeof(sml_open_request));
	return open_request;
}

/*
sml_open_request *sml_open_request_init(char* client_id,char* req_file_id, char* server_id){
	sml_open_request *open_request = (sml_open_request *) malloc(sizeof(sml_open_request));
	memset(open_request, 0, sizeof(sml_open_request));

		   // printf("TODO: %s\n", __FUNCTION__);
	open_request->client_id = sml_octet_string_init((unsigned char *)client_id,strlen(client_id));
	open_request->req_file_id = sml_octet_string_init((unsigned char *)req_file_id,strlen(req_file_id));
	open_request->server_id = sml_octet_string_init((unsigned char *)server_id, strlen(server_id));
	return open_request;
}

sml_open_request *sml_open_request_init() {
   // sml_open_request *open_request = (sml_open_request *) malloc(sizeof(sml_open_request));
    //memset(open_request, 0, sizeof(sml_open_request));
    
   // printf("TODO: %s\n", __FUNCTION__);
    //open_request->username = sml_octet_string_init((unsigned char *)"kunde",5);
    //open_request->username = sml_octet_string_init((unsigned char *)"kunde",5);
    //open_request->client_id = sml_octet_string_init((unsigned char *)"SEDICMA", 7);
    //open_request->req_file_id = sml_octet_string_init((unsigned char *)"01", 2);
    char server_id[] ={0x06, 0x45, 0x4d, 0x48, 0x01, 0x02, 0x71, 0x53, 0x3b, 0xcd};
    //open_request->server_id = sml_octet_string_init(server_id, 10);
    return sml_open_request_init("SEDICMA", "02", server_id);
}
*/
void sml_open_request_write(sml_open_request *msg, sml_buffer *buf) {
    sml_buf_set_type_and_length(buf, SML_TYPE_LIST, 7);
    
    mc_sml_optional_write(buf);
    sml_octet_string_write(msg->client_id, buf);
    sml_octet_string_write(msg->req_file_id, buf);
    sml_octet_string_write(msg->server_id, buf);
    sml_octet_string_write(msg->username,buf);
    sml_octet_string_write(msg->password,buf);
    mc_sml_optional_write(buf);

}

sml_open_request *sml_open_request_parse(sml_buffer *buf) {
    sml_open_request *msg = (sml_open_request *) malloc(sizeof(sml_open_request));
    memset(msg, 0, sizeof(sml_open_request));
    
    if (mc_sml_buf_get_current_type(buf) != SML_TYPE_LIST) {
		buf->error = 1;
		goto error;
	}
	
	if (sml_buf_get_next_length(buf) != 7) {
		buf->error = 1;
		goto error;
	}
    
    msg->codepage = SML_SKIP_OPTIONAL sml_octet_string_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;
    
    msg->client_id = sml_octet_string_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;
    
    msg->req_file_id = sml_octet_string_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;
    
    msg->server_id = SML_SKIP_OPTIONAL sml_octet_string_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;
    
    msg->username = SML_SKIP_OPTIONAL sml_octet_string_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;
    
    msg->password = SML_SKIP_OPTIONAL sml_octet_string_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;
    
    msg->sml_version = SML_SKIP_OPTIONAL mc_sml_parse_u8(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;
    
    return msg;
    
error: 
	free(msg);
	return 0;
}

void sml_open_request_free(sml_open_request *msg) {
	free(msg->client_id);
	free(msg->password);
	free(msg->req_file_id);
	free(msg->server_id);
	free(msg->username);
	free(msg);
   // printf("NYI: %s\n", __FUNCTION__);
}


