#ifndef _SML_OPEN_REQUEST_H
#define	_SML_OPEN_REQUEST_H

#include "sml_shared.h"
#include "sml_octet_string.h"


#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    octet_string *codepage; // optional
	octet_string *client_id; 
	octet_string *req_file_id;
	octet_string *server_id; // optional
	octet_string *username; // optional
	octet_string *password; // optional
	u8 sml_version; // optional
} sml_open_request;

//sml_open_request *sml_open_request_init();

//sml_open_request *sml_open_request_init(char* client_id,char* req_file_id, char* server_id);

sml_open_request *sml_open_request_init();

void sml_open_request_write(sml_open_request *msg, sml_buffer *buf);

sml_open_request *sml_open_request_parse(sml_buffer *buf);

void sml_open_request_free(sml_open_request *msg);

#ifdef __cplusplus
}
#endif


#endif
