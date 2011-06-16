#ifndef _SML_TRANSPORT_H
#define	_SML_TRANSPORT_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif


//void (*mc_sml_transport_receiver_fun)(unsigned char *buffer, size_t buffer_len) = 0;

void mc_sml_transport_listen(int fd, void (*mc_sml_transport_receiver)(unsigned char *buffer, size_t buffer_len));
#ifdef __cplusplus
}
#endif

#endif

