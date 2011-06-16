
#include <sml/sml_close_request.h>

#include <stdio.h>

sml_close_request *sml_close_request_init() {
    sml_close_request *close_request = (sml_close_request *) malloc(sizeof(sml_close_request));
    memset(close_request, 0, sizeof(sml_close_request));
    return close_request;
}

void sml_close_request_write(sml_close_request *msg, sml_buffer *buf) {
    mc_sml_set_type_and_length(buf, SML_TYPE_LIST, 1);

    if (msg->global_signature != NULL){
    	sml_octet_string_write(msg->global_signature,buf);
    } else mc_sml_optional_write(buf);
}

sml_close_request * sml_close_request_parse(sml_buffer *buf) {
    sml_close_request *msg = (sml_close_request *) malloc(sizeof(sml_close_request));
    memset(msg, 0, sizeof(sml_close_request));
    
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

void sml_close_request_free(sml_close_request *msg) {
	if (msg) {
		sml_octet_string_free(msg->global_signature);		
		free(msg);

	}
}


