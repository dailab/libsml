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


#include <sml/sml_message.h>
#include <sml/sml_number.h>
#include <sml/sml_octet_string.h>
#include <sml/sml_shared.h>
#include <sml/sml_list.h>
#include <sml/sml_time.h>
#include <sml/sml_crc16.h>
#include <sml/sml_get_proc_parameter_request.h>
#include <sml/sml_set_proc_parameter_request.h>
#include <sml/sml_get_profile_pack_request.h>
#include <sml/sml_get_list_request.h>
#include <sml/sml_get_list_response.h>
#include <sml/sml_attention_response.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SML_MESSAGE_TRANSACTION_MAGIC_NUMBER 0x6F4D654E   

// SML MESSAGE

sml_message *sml_message_parse(sml_buffer *buf) {
	sml_message *msg = (sml_message *) malloc(sizeof(sml_message));
	memset(msg, 0, sizeof(sml_message));
	
	if (sml_buf_get_next_type(buf) != SML_TYPE_LIST) {
		buf->error = 1;
		goto error;
	}
	
	if (sml_buf_get_next_length(buf) != 6) {
		buf->error = 1;
		goto error;
	}
	
	msg->transaction_id = sml_octet_string_parse(buf);
	if (sml_buf_has_errors(buf)) goto error;
	
	msg->group_id = mc_sml_parse_u8(buf);
	if (sml_buf_has_errors(buf)) goto error;
	
	msg->abort_on_error = mc_sml_parse_u8(buf);
	if (sml_buf_has_errors(buf)) goto error;
	
	msg->message_body = sml_message_body_parse(buf);
	if (sml_buf_has_errors(buf)) goto error;
    
	msg->crc = mc_sml_parse_u16(buf);
	if (sml_buf_has_errors(buf)) goto error;
	
	if (sml_buf_get_current_byte(buf) == SML_MESSAGE_END) {
		sml_buf_update_bytes_read(buf, 1);
	}
	return msg;
    
error:
	// TODO: free encapsulated stuff 
	free(msg);
	return 0;
}

sml_message *sml_message_init() {
    sml_message *msg = (sml_message *) malloc(sizeof(sml_message));
    memset(msg, 0, sizeof(sml_message));
    
    int id = ((unsigned int) getpid()) | SML_MESSAGE_TRANSACTION_MAGIC_NUMBER;
    msg->transaction_id = sml_octet_string_init((unsigned char *)&id, sizeof(int));
    
    return msg;
}
void sml_message_free(sml_message *msg) {
    if (msg) {
        if (msg->transaction_id) 
            sml_octet_string_free(msg->transaction_id);
        if (msg->message_body)
            sml_message_body_free(msg->message_body);
        free(msg);
    }
}

void sml_message_write(sml_message *msg, sml_buffer *buf) {
    int msg_start = buf->cursor;
    sml_buf_set_type_and_length(buf, SML_TYPE_LIST, 6);
    sml_octet_string_write(msg->transaction_id, buf);
    sml_number_write(SML_TYPE_UNSIGNED, SML_TYPE_NUMBER_8, (u64) msg->group_id, buf);
    sml_number_write(SML_TYPE_UNSIGNED, SML_TYPE_NUMBER_8, (u64) msg->abort_on_error, buf);
    sml_message_body_write(msg->message_body, buf);
    
    msg->crc = sml_crc16_calculate(&(buf->buffer[msg_start]), buf->cursor - msg_start);
    
    sml_number_write(SML_TYPE_UNSIGNED, SML_TYPE_NUMBER_16, (u64) msg->crc, buf);
    
    // end of message
    buf->buffer[buf->cursor] = 0x0;
    buf->cursor++;
}

// SML MESSAGE BODY

sml_message_body *sml_message_body_parse(sml_buffer *buf) {
	sml_message_body *msg_body = (sml_message_body *) malloc(sizeof(sml_message_body));
	memset(msg_body, 0, sizeof(sml_message_body));
	
	if (sml_buf_get_next_type(buf) != SML_TYPE_LIST) {
		buf->error = 1;
		goto error;
	}
	
	if (sml_buf_get_next_length(buf) != 2) {
		buf->error = 1;
		goto error;
	}
	
	msg_body->tag = mc_sml_parse_u16(buf);
	if (sml_buf_has_errors(buf)) goto error;
	
	switch (msg_body->tag) {
        case SML_MESSAGE_OPEN_REQUEST:
            msg_body->data = sml_open_request_parse(buf);
            break;
        case SML_MESSAGE_OPEN_RESPONSE:
			msg_body->data = sml_open_response_parse(buf);
			break;
        case SML_MESSAGE_CLOSE_REQUEST:
            msg_body->data = sml_close_request_parse(buf);
            break;
        case SML_MESSAGE_CLOSE_RESPONSE:
            msg_body->data = sml_close_response_parse(buf);
            break;
		case SML_MESSAGE_GET_LIST_RESPONSE:
			msg_body->data = sml_get_list_response_parse(buf);
			break;
		case SML_MESSAGE_GET_LIST_REQUEST:
			msg_body->data = sml_get_list_request_parse(buf);
			break;
		case SML_MESSAGE_ATTENTION_RESPONSE:
			msg_body->data = sml_attention_response_parse(buf);
			break;
        default:
            printf("error: message type %04X not yet implemented\n", msg_body->tag);
			break;
	}
	
	return msg_body;
    
error:
	free(msg_body);
	return 0;
}

sml_message_body *sml_message_body_init(u16 tag, void *data) {
    sml_message_body *message_body = (sml_message_body *) malloc(sizeof(sml_message_body));
    memset(message_body, 0, sizeof(sml_message_body));
    message_body->tag = tag;
    message_body->data = data;
    return message_body;
}

void sml_message_body_write(sml_message_body *message_body, sml_buffer *buf) {
    sml_buf_set_type_and_length(buf, SML_TYPE_LIST, 2);
    sml_number_write(SML_TYPE_UNSIGNED, SML_TYPE_NUMBER_16, (u64) message_body->tag, buf);
    
    switch (message_body->tag) {
        case SML_MESSAGE_OPEN_REQUEST:
            sml_open_request_write((sml_open_request *) message_body->data, buf);
			break;
        case SML_MESSAGE_CLOSE_REQUEST:
            sml_close_request_write((sml_close_request *) message_body->data, buf);
            break;
        case SML_MESSAGE_SET_PROC_PARAMETER_REQUEST:
            sml_set_proc_parameter_request_write((sml_set_proc_parameter_request *) message_body->data, buf);
            break;
        case SML_MESSAGE_GET_PROC_PARAMETER_REQUEST:
            sml_get_proc_parameter_request_write((sml_get_proc_parameter_request *) message_body->data, buf);
            break;
        case SML_MESSAGE_GET_LIST_REQUEST:
        	sml_get_list_request_write((sml_get_list_request *)message_body->data, buf);
        	break;
        case SML_MESSAGE_GET_PROFILE_PACK_REQUEST:
           	sml_get_profile_pack_request_write((sml_get_profile_pack_request *)message_body->data, buf);
           	break;
		default:
            printf("error: message type %04X not yet implemented\n", message_body->tag);
			break;
    }
}

void sml_message_body_free(sml_message_body *message_body) {
    if (message_body) {
        switch (message_body->tag) {
            case SML_MESSAGE_OPEN_REQUEST:
                sml_open_request_free((sml_open_request *) message_body->data);
                break;
            case SML_MESSAGE_OPEN_RESPONSE:
                sml_open_response_free((sml_open_response *) message_body->data);
                break;
            case SML_MESSAGE_CLOSE_REQUEST:
                sml_close_request_free((sml_close_request *) message_body->data);
                break;
            case SML_MESSAGE_CLOSE_RESPONSE:
                sml_close_response_free((sml_close_response *) message_body->data);
                break;
            case SML_MESSAGE_SET_PROC_PARAMETER_REQUEST:
                sml_set_proc_parameter_request_free((sml_set_proc_parameter_request *) message_body->data);
                break;
            case SML_MESSAGE_GET_LIST_REQUEST:
                sml_get_list_request_free((sml_get_list_request *) message_body->data);
                break;
            case SML_MESSAGE_GET_LIST_RESPONSE:
                sml_get_list_response_free((sml_get_list_response *) message_body->data);
                break;
            default:
                printf("NYI: %s for message type %04X\n", __FUNCTION__, message_body->tag);
                break;
        }
        
        free(message_body);
    }
}

