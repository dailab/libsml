#ifndef _SML_GET_PROFILE_PACK_REQUEST_H
#define _SML_GET_PROFILE_PACK_REQUEST_H

#include "sml_shared.h"
#include "sml_octet_string.h"
#include "sml_time.h"
#include "sml_list.h"
#include "sml_tree.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
	octet_string *server_id;	// optional
	octet_string *username; 	//  optional
	octet_string *password; 	//  optional
	sml_boolean with_rawdata;  // optional
	sml_time *begin_time;		// optional
	sml_time *end_time;			// optional
	sml_tree_path *parameter_tree_path;
	// sml_object_list * object_list; // optional		sml_object_list not implemented yet
	sml_tree *das_details;		// optional
} sml_get_profile_pack_request;


sml_get_profile_pack_request *sml_get_profile_pack_request_parse(sml_buffer *buf);

sml_get_profile_pack_request *sml_get_profile_pack_request_init();

void sml_get_profile_pack_request_write(sml_get_profile_pack_request *msg, sml_buffer *buf);

void sml_get_profile_pack_request_free(sml_get_profile_pack_request *msg);


#ifdef __cplusplus
}
#endif


#endif
