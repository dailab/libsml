
#ifndef _SML_ATTENTION_RESPONSE_H
#define	_SML_ATTENTION_RESPONSE_H

#include "sml_shared.h"
#include "sml_octet_string.h"
#include "sml_tree.h"


#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
	octet_string *server_id;
	octet_string *attention_number;
	octet_string *attention_message; // optional
	sml_tree *attention_details;	 // optional
} sml_attention_response;

sml_attention_response *sml_attention_response_parse(sml_buffer *buf);

void sml_attention_response_free(sml_attention_response *msg);

#ifdef __cplusplus
}
#endif


#endif
