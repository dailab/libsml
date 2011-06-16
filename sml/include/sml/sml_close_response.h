
#ifndef _SML_CLOSE_RESPONSE_H
#define _SML_CLOSE_RESPONSE_H

#include "sml_close_request.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef sml_close_request sml_close_response;

sml_close_response *sml_close_response_parse(sml_buffer *buf);

void sml_close_response_free(sml_close_response *msg);

#ifdef __cplusplus
}
#endif


#endif

