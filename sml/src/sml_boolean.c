
#include <sml/sml_boolean.h>
#include <stdio.h>

sml_boolean sml_boolean_parse(sml_buffer *buf) {
    printf("NYI: %s\n", __FUNCTION__);
    return 0;
}

void sml_boolean_write(sml_boolean boolean, sml_buffer *buf) {
    mc_sml_set_type_and_length(buf, SML_TYPE_BOOLEAN, 1);
    if (boolean == SML_BOOLEAN_FALSE) {
        buf->buffer[buf->cursor] = SML_BOOLEAN_FALSE;
    }
    else {
        buf->buffer[buf->cursor] = SML_BOOLEAN_TRUE;
    }
    buf->cursor++;
}



