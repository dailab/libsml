
#include <sml/sml_get_list_response.h>


sml_get_list_response *sml_get_list_response_parse(sml_buffer *buf) {
	

	sml_get_list_response *msg = (sml_get_list_response *) malloc(sizeof(sml_get_list_response));
	memset(msg, 0, sizeof(sml_get_list_response));
	
	if (mc_sml_buf_get_current_type(buf) != SML_TYPE_LIST) {
		buf->error = 1;
		goto error;
	}
	
	if (mc_sml_get_length(buf) != 7) {
		buf->error = 1;
		goto error;
	}

	msg->client_id = SML_SKIP_OPTIONAL sml_octet_string_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;

	msg->server_id = sml_octet_string_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;

	msg->list_name = SML_SKIP_OPTIONAL sml_octet_string_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;

	msg->act_sensor_time = SML_SKIP_OPTIONAL sml_time_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;

	msg->val_list = sml_list_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;

	msg->list_signature = SML_SKIP_OPTIONAL sml_octet_string_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;

	msg->act_gateway_time = SML_SKIP_OPTIONAL sml_time_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;

	return msg;
	
error: 
	free(msg);
	return 0;
    
}

void sml_get_list_response_free(sml_get_list_response *msg) {
    if (msg) {
        sml_octet_string_free(msg->client_id);
        sml_octet_string_free(msg->server_id);
        sml_octet_string_free(msg->list_name);
        sml_time_free(msg->act_sensor_time);
        sml_list_free(msg->val_list);
        sml_octet_string_free(msg->list_signature);
        sml_time_free(msg->act_gateway_time);
        free(msg);
    }
}
