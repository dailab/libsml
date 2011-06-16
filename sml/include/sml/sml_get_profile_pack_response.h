#ifndef _SML_GET_PROFILE_PACK_RESPONSE_H
#define _SML_GET_PROFILE_PACK_RESPONSE_H

#include "sml_shared.h"
#include "sml_octet_string.h"
#include "sml_time.h"
#include "sml_list.h"
#include "sml_tree.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
	octet_string *server_id;
	sml_time *act_time; // specified by germans (current time was meant) ;)
	u32 *reg_period;
	sml_tree_path *parameter_tree_path;
	sml_list *list_of_sml_prof_obj_header_entry;
	sml_list *list_of_sml_prof_obj_period_entry;
	octet_string *rawdata;  			// optional
	sml_signature *profile_signature; 	// optional

} sml_get_profile_pack_response;

sml_get_profile_pack_response *sml_get_profile_pack_response_parse(sml_buffer *buf);

void sml_get_profile_pack_response_free(sml_get_profile_pack_response *msg);

#ifdef __cplusplus
}
#endif


#endif
