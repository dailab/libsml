
#ifndef _SML_OPEN_RESPONSE_H
#define	_SML_OPEN_RESPONSE_H

#include "sml_shared.h"
#include "sml_octet_string.h"
#include "sml_time.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
	octet_string *codepage; // optional
	octet_string *client_id; // optional
	octet_string *req_file_id;
	octet_string *server_id;
	sml_time *ref_time; // optional
	u8 sml_version; // optional
} sml_open_response;

sml_open_response *sml_open_response_parse(sml_buffer *buf);

void sml_open_response_free(sml_open_response *msg);

#ifdef __cplusplus
}
#endif


#endif
