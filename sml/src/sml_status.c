
#include <sml/sml_status.h>
#include <sml/sml_shared.h>

sml_status *sml_status_parse(sml_buffer *buf) {
	int type = mc_sml_buf_get_current_type(buf);
	unsigned char byte = mc_sml_buf_get_current_byte(buf);
	
	sml_status *state = (sml_status *) malloc(sizeof(sml_status));
	switch (type) {
		case SML_TYPE_UNSIGNED:
			switch (byte & SML_LENGTH_FIELD) {
				case SML_TYPE_NUMBER_8:
					state->status8 = mc_sml_parse_u8(buf);
					break;
				case SML_TYPE_NUMBER_16:
					state->status16 = mc_sml_parse_u16(buf);
					break;
				case SML_TYPE_NUMBER_16 + 1:
				case SML_TYPE_NUMBER_32:
					state->status32 = mc_sml_parse_u32(buf);
					break;
				case SML_TYPE_NUMBER_32 + 1:
				case SML_TYPE_NUMBER_32 + 2:
				case SML_TYPE_NUMBER_32 + 3:
				case SML_TYPE_NUMBER_64:
					state->status64 = mc_sml_parse_u64(buf);
					break;
				default:
					buf->error = 1;
					break;
			}
			break;
		default:
			buf->error = 1;
			break;
	}
	if (mc_sml_buf_has_errors(buf)) {
		free(state);
		return 0;
	}
	
	return state;
}

void sml_status_free(sml_status *status) {
    if (status) {
        free(status);
    }
}
