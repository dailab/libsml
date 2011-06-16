
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
    mc_sml_set_type_and_length(buf, SML_TYPE_LIST, 9);

    // server_id
    if (msg->server_id != NULL) {
    	sml_octet_string_write(msg->server_id,buf);
    } else mc_sml_optional_write(buf);

    // username
    if (msg->username != NULL) {
    	sml_octet_string_write(msg->username,buf);
    } else mc_sml_optional_write(buf);

    // password
    if (msg->password != NULL) {
    	sml_octet_string_write(msg->password,buf);
    } else mc_sml_optional_write(buf);

    // with_rawdata
    if (msg->with_rawdata != NULL) {
      printf("TODO: %s - comparision is not valid", __FUNCTION__);
    	sml_boolean_write(msg->with_rawdata,buf);
    } else mc_sml_optional_write(buf); // with_rawdata

    // begin_time
    if (msg->begin_time != NULL){
    	sml_time_write(msg->begin_time, buf);
    } else mc_sml_optional_write(buf); // begin_time
    mc_sml_optional_write(buf); // end_time

    // parameter_tree_path is not optional
    sml_tree_path_write(msg->parameter_tree_path, buf);

    mc_sml_optional_write(buf); // object_list
    mc_sml_optional_write(buf); // das_details
    printf("request_write");
}


sml_get_profile_pack_request *sml_get_profile_pack_request_parse(sml_buffer *buf) {
	
	sml_get_profile_pack_request *msg = (sml_get_profile_pack_request *) malloc(sizeof(sml_get_profile_pack_request));
	memset(msg, 0, sizeof(sml_get_profile_pack_request));
	
	if (mc_sml_buf_get_current_type(buf) != SML_TYPE_LIST) {
		buf->error = 1;
		goto error;
	}
	
	if (mc_sml_get_length(buf) != 9) {
		buf->error = 1;
		goto error;
	}
	
	printf("TODO:sml_get_profile_pack_request_parse -> not implemented yet");

/*	msg->client_id = SML_SKIP_OPTIONAL sml_octet_string_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;
	
	msg->server_id = sml_octet_string_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;
	
	msg->list_name = SML_SKIP_OPTIONAL sml_octet_string_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;
	*/
	/*msg->act_sensor_time = SML_SKIP_OPTIONAL sml_time_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;
    
	msg->val_list = sml_list_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;
	
	msg->list_signature = SML_SKIP_OPTIONAL sml_octet_string_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;
    
	msg->act_gateway_time = SML_SKIP_OPTIONAL sml_time_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;
	*/
	return msg;
	
  error:
	free(msg);
	return 0;
    
}

void sml_get_profile_pack_request_free(sml_get_profile_pack_request *msg){
	 printf("NYI: %s\n", __FUNCTION__);
}


