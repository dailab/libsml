#ifndef _SML_CLOSE_REQUEST_H
#define _SML_CLOSE_REQUEST_H

#include "sml_shared.h"
#include "sml_octet_string.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    sml_signature *global_signature; // optional
} sml_close_request;

sml_close_request *sml_close_request_init();

void sml_close_request_write(sml_close_request *msg, sml_buffer *buf);

sml_close_request * sml_close_request_parse(sml_buffer *buf);

void sml_close_request_free(sml_close_request *msg);

#ifdef __cplusplus
}
#endif


#endif
