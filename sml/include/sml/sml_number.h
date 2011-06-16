
#ifndef _SML_NUMBER_H
#define	_SML_NUMBER_H

#include "sml_shared.h"

#ifdef __cplusplus
extern "C" {
#endif


// Parses a number. Identified by type (SML_TYPE_INTEGER or SML_TYPE_UNSIGNED) 
// and maximal number of bytes (SML_TYPE_NUMBER_8, SML_TYPE_NUMBER_16, 
// SML_TYPE_NUMBER_32, SML_TYPE_NUMBER_64)
u64 mc_sml_parse_number(sml_buffer *buf, unsigned char type, int max_size);

#define mc_sml_parse_u8(buf) (u8) mc_sml_parse_number(buf, SML_TYPE_UNSIGNED, SML_TYPE_NUMBER_8)
#define mc_sml_parse_u16(buf) (u16) mc_sml_parse_number(buf, SML_TYPE_UNSIGNED, SML_TYPE_NUMBER_16)
#define mc_sml_parse_u32(buf) (u32) mc_sml_parse_number(buf, SML_TYPE_UNSIGNED, SML_TYPE_NUMBER_32)
#define mc_sml_parse_u64(buf) (u64) mc_sml_parse_number(buf, SML_TYPE_UNSIGNED, SML_TYPE_NUMBER_64)
#define mc_sml_parse_i8(buf) (i8) mc_sml_parse_number(buf, SML_TYPE_INTEGER, SML_TYPE_NUMBER_8)
#define mc_sml_parse_i16(buf) (i16) mc_sml_parse_number(buf, SML_TYPE_INTEGER, SML_TYPE_NUMBER_16)
#define mc_sml_parse_i32(buf) (i32) mc_sml_parse_number(buf, SML_TYPE_INTEGER, SML_TYPE_NUMBER_32)
#define mc_sml_parse_i64(buf) (i64) mc_sml_parse_number(buf, SML_TYPE_INTEGER, SML_TYPE_NUMBER_64)

void sml_number_write(unsigned char type, int size, u64 value, sml_buffer *buf);

typedef u8 sml_unit;

#ifdef __cplusplus
}
#endif


#endif
