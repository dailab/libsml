
#include <sml/sml_number.h>
#include <string.h>
#include <stdio.h>

u64 mc_sml_parse_number(sml_buffer *buf, unsigned char type, int max_size) {

	int l, i;
	u64 n = 0;
	if (mc_sml_buf_get_current_type(buf) != type) {
		buf->error = 1;
		return 0;
	}
	
	l = mc_sml_get_length(buf);
	if (l < 0 || l > max_size) {
		buf->error = 1;
		return 0;
	}
	
	// TODO: this doesn't work for integers (leading 1's)
	// mathias runge: -> fixed bug in sml_value_parse for SML_TYPE_INTEGER -> see comment in sml_value.cpp
	//					 maybe this one is fixed too?
	for (i = 0; i < l; i++) {
		n <<= 8;
		n |= mc_sml_buf_get_current_byte(buf);
		mc_sml_buf_update_read_bytes(buf, 1);
	}
	return n;
}

void sml_number_write(unsigned char type, int size, u64 value, sml_buffer *buf) {
    mc_sml_set_type_and_length(buf, type, size);
    int i;
    u64 mask = 0xFF;
    mask <<= (8 * (size - 1));
    
    for (i = 0; i < size; i++) {
        buf->buffer[buf->cursor + i] = (unsigned char) ((mask & value) >> (8 * (size - i - 1)));
        mask >>= 8;
    }
    buf->cursor += size;
}
