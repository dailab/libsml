
#include <sml/sml_attention_response.h>
#include <sml/sml_tree.h>

sml_attention_response *sml_attention_response_parse(sml_buffer *buf){
	sml_attention_response *msg = (sml_attention_response *) malloc(sizeof(sml_attention_response));
	memset(msg, 0, sizeof(sml_attention_response));

	if (mc_sml_buf_get_current_type(buf) != SML_TYPE_LIST) {
		buf->error = 1;
		goto error;
	}

	if (mc_sml_get_length(buf) != 4) {
		buf->error = 1;
		goto error;
	}

	msg->server_id = sml_octet_string_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;

	msg->attention_number = sml_octet_string_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;

	msg->attention_message = SML_SKIP_OPTIONAL sml_octet_string_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;

	msg->attention_details = SML_SKIP_OPTIONAL sml_tree_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;
	
	return msg;
	
	error:
		free(msg);
		return 0;
	
}

void sml_attention_response_free(sml_attention_response *msg){
	if (msg) {
	   sml_octet_string_free(msg->server_id);
	   sml_octet_string_free(msg->attention_number);
	   sml_octet_string_free(msg->attention_message);
	   sml_tree_free(msg->attention_details);
	   free(msg);
	 }
}
