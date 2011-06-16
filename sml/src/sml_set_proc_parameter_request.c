
#include <sml/sml_set_proc_parameter_request.h>

#include <stdio.h>

sml_set_proc_parameter_request *sml_set_proc_parameter_request_init() {
    sml_set_proc_parameter_request *msg = (sml_set_proc_parameter_request *) malloc(sizeof (sml_set_proc_parameter_request));
    memset(msg, 0, sizeof(sml_set_proc_parameter_request));
    return msg;
}

void sml_set_proc_parameter_request_write(sml_set_proc_parameter_request *msg, sml_buffer *buf) {
    mc_sml_set_type_and_length(buf, SML_TYPE_LIST, 5);
    mc_sml_optional_write(buf);
    mc_sml_optional_write(buf);
    mc_sml_optional_write(buf);
    sml_tree_path_write(msg->parameter_tree_path, buf);
    sml_tree_write(msg->parameter_tree, buf);
}

void sml_set_proc_parameter_request_free(sml_set_proc_parameter_request *msg) {
    printf("NYI: %s\n", __FUNCTION__);
}



