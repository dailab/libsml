#ifndef _SML_BOOLEAN_H
#define	_SML_BOOLEAN_H

#define SML_BOOLEAN_TRUE 0xFF
#define SML_BOOLEAN_FALSE 0x00

#include "sml_shared.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef u8 sml_boolean;

sml_boolean sml_boolean_parse(sml_buffer *buf);
void sml_boolean_write(sml_boolean boolean, sml_buffer *buf);

#ifdef __cplusplus
}
#endif


#endif
