#ifndef _SML_STATUS_H
#define	_SML_STATUS_H

#include "sml_number.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef union {
	u8 status8;
	u16 status16;
	u32 status32;
	u64 status64;
} sml_status;

sml_status *sml_status_parse(sml_buffer *buf);

void sml_status_free(sml_status *status);
#ifdef __cplusplus
}
#endif

#endif 

