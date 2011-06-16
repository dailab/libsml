
#include <sml/sml_open_response.h>

#include <sml/sml_number.h>

sml_open_response *sml_open_response_parse(sml_buffer *buf) {
	sml_open_response *msg = (sml_open_response *) malloc(sizeof(sml_open_response));
	memset(msg, 0, sizeof(sml_open_response));
	
	if (mc_sml_buf_get_current_type(buf) != SML_TYPE_LIST) {
		buf->error = 1;
		goto error;
	}
	
	if (mc_sml_get_length(buf) != 6) {
		buf->error = 1;
		goto error;
	}
	
	msg->codepage = SML_SKIP_OPTIONAL sml_octet_string_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;
	
	msg->client_id = SML_SKIP_OPTIONAL sml_octet_string_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;
	
	msg->req_file_id = sml_octet_string_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;
	
	msg->server_id = sml_octet_string_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;
	
	msg->ref_time = SML_SKIP_OPTIONAL sml_time_parse(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;
	
	msg->sml_version = SML_SKIP_OPTIONAL mc_sml_parse_u8(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;
	
	return msg;
error:
	free(msg);
	return 0;
}

void sml_open_response_free(sml_open_response *msg) {
    if (msg) {
        sml_octet_string_free(msg->codepage);
        sml_octet_string_free(msg->client_id);
        sml_octet_string_free(msg->req_file_id);
        sml_octet_string_free(msg->server_id);
        sml_time_free(msg->ref_time);
        free(msg);
    }
}
