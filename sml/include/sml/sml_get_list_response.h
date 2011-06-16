#ifndef _SML_GET_LIST_RESPONSE_H
#define _SML_GET_LIST_RESPONSE_H

#include "sml_shared.h"
#include "sml_octet_string.h"
#include "sml_time.h"
#include "sml_list.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
	octet_string *client_id;  // optional
	octet_string *server_id;
	octet_string *list_name; //  optional
	sml_time *act_sensor_time; // optional
	sml_list *val_list;
	sml_signature *list_signature; // optional
	sml_time *act_gateway_time; // optional
} sml_get_list_response;

sml_get_list_response *sml_get_list_response_parse(sml_buffer *buf);

void sml_get_list_response_free(sml_get_list_response *msg);

#ifdef __cplusplus
}
#endif


#endif
