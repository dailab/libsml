#ifndef _SML_VALUE_H
#define	_SML_VALUE_H

#include "sml_shared.h"
#include "sml_octet_string.h"
#include "sml_number.h"
#include "sml_boolean.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    u8 type;
    union {
        sml_boolean boolean;
        octet_string *bytes; // can has zero length
        i8 int8;
        i16 int16;
        i32 int32;
        i64 int64;
        u8 uint8;
        u16 uint16;
        u32 uint32;
        u64 uint64;
    } data;
} sml_value;

sml_value *sml_value_parse(sml_buffer *buf);
void sml_value_write(sml_value *value, sml_buffer *buf);
sml_value *sml_value_init();
void sml_value_free(sml_value *value);

#ifdef __cplusplus
}
#endif

#endif
