#ifndef _SML_GET_PROC_PARAMETER_REQUEST_H
#define _SML_GET_PROC_PARAMETER_REQUEST_H

#include "sml_shared.h"
#include "sml_octet_string.h"
#include "sml_tree.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    octet_string *server_id; // optional
    octet_string *username; // optional 
    octet_string *password; // optional
    sml_tree_path *parameter_tree_path; 
    sml_tree *parameter_tree;
} sml_get_proc_parameter_request;

sml_get_proc_parameter_request *sml_get_proc_parameter_request_init();

void sml_get_proc_parameter_request_write(sml_get_proc_parameter_request *msg, sml_buffer *buf);

void sml_get_proc_parameter_request_free(sml_get_proc_parameter_request *msg);

#ifdef __cplusplus
}
#endif


#endif
