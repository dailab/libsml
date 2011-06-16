
#ifndef _SML_TIME_H
#define	_SML_TIME_H

#include "sml_shared.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
	u8 tag;
	u32 data;
} sml_time;

// Parses a time, updates the buffer accordingly, memory must be free'd elsewhere.
sml_time *sml_time_parse(sml_buffer *buf);
void sml_time_write(sml_time *time, sml_buffer *buf);
void sml_time_free(sml_time *time);
#ifdef __cplusplus
}
#endif

#endif
