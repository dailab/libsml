
#include <sml/sml_time.h>
#include <sml/sml_shared.h>
#include <sml/sml_number.h>
#include <stdio.h>

sml_time *sml_time_parse(sml_buffer *buf) {
	sml_time *tme = (sml_time *) malloc(sizeof(sml_time));
	
	if (mc_sml_buf_get_current_type(buf) != SML_TYPE_LIST) {
		buf->error = 1;
		goto error;
	}
	
	if (mc_sml_get_length(buf) != 2) {
		buf->error = 1;
		goto error;
	}
	
	tme->tag = mc_sml_parse_u8(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;
	
	tme->data = mc_sml_parse_u32(buf);
	if (mc_sml_buf_has_errors(buf)) goto error;
	
	return tme;
	
error:
	free(tme);
	return 0;
}

void sml_time_write(sml_time *time, sml_buffer *buf){
	 printf("NYI: %s (writing optional flag instead)\n", __FUNCTION__);
	 mc_sml_optional_write(buf);
}

void sml_time_free(sml_time *time) {
    if (time) {
        free(time);
    }
}
