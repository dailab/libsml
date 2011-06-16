
#include <sml/sml_close_response.h>
#include <stdio.h>

sml_close_response *sml_close_response_parse(sml_buffer *buf) {
    
    sml_close_response *msg = (sml_close_response *) malloc(sizeof(sml_close_response));
    memset(msg, 0, sizeof(sml_close_response));
    
    if (mc_sml_buf_get_current_type(buf) != SML_TYPE_LIST) {
		buf->error = 1;
		goto error;
	}
	
	if (mc_sml_get_length(buf) != 1) {
		buf->error = 1;
		goto error;
	}
    
    msg->global_signature = SML_SKIP_OPTIONAL sml_octet_string_parse(buf);
    if (mc_sml_buf_has_errors(buf)) goto error;
    
    return msg;
    
error: 
	free(msg);
	return 0;
    
}

void sml_close_response_free(sml_close_response *msg) {
    if (msg) {
        sml_octet_string_free(msg->global_signature);      
        free(msg);
    }
}
