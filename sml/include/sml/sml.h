#ifndef _SML_H
#define	_SML_H

#include "sml_message.h"
#include "sml_shared.h"

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    sml_message **messages;
    short messages_len;
    sml_buffer *buf;
} sml_file;

// Parses a SML file.
sml_file *sml_file_parse(unsigned char *buffer, size_t buffer_len);
sml_file *sml_file_init();
void sml_file_add_message(sml_file *file, sml_message *message);
void sml_file_write(sml_file *file);
void sml_file_free(sml_file *file);
void sml_file_print(sml_file *file);

void mc_sml_hexdump(unsigned char *buffer, size_t buffer_len);

#ifdef __cplusplus
}
#endif


#endif 
