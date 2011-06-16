

#include <sml/sml_get_proc_parameter_request.h>
#include <sml/sml_tree.h>
#include <stdio.h>

sml_get_proc_parameter_request *sml_get_proc_parameter_request_init() {
    sml_get_proc_parameter_request *msg = (sml_get_proc_parameter_request *) malloc(sizeof (sml_get_proc_parameter_request));
    memset(msg, 0, sizeof(sml_get_proc_parameter_request));
    return msg;
}

void sml_get_proc_parameter_request_write(sml_get_proc_parameter_request *msg, sml_buffer *buf) {
    mc_sml_set_type_and_length(buf, SML_TYPE_LIST, 5);

    // optional server_id
    if (msg->server_id != NULL){
    	sml_octet_string_write(msg->server_id, buf);
    } else  mc_sml_optional_write(buf);

    // optional username
    if (msg->username != NULL) {
    	sml_octet_string_write(msg->username, buf);
    } else mc_sml_optional_write(buf);

    // optional password
    if (msg->password != NULL){
    	sml_octet_string_write(msg->password, buf);
    } else mc_sml_optional_write(buf);

    sml_tree_path_write(msg->parameter_tree_path, buf);

    sml_tree_write(msg->parameter_tree, buf);
}

void sml_get_proc_parameter_request_free(sml_get_proc_parameter_request *msg) {
   if (msg){
	   sml_octet_string_free(msg->server_id);
	   sml_octet_string_free(msg->username);
	   sml_octet_string_free(msg->password);
	   sml_tree_path_free(msg->parameter_tree_path);
	   sml_tree_free(msg->parameter_tree);
	   free(msg);
   }
}
