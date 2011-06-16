// Copyright 2011 Juri Glass, Mathias Runge, Nadim El Sayed 
// DAI-Labor, TU-Berlin
// 
// This file is part of libSML.
// 
// libSML is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// libSML is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with libSML.  If not, see <http://www.gnu.org/licenses/>.


#include <sml/sml_set_proc_parameter_request.h>

#include <stdio.h>

sml_set_proc_parameter_request *sml_set_proc_parameter_request_init() {
    sml_set_proc_parameter_request *msg = (sml_set_proc_parameter_request *) malloc(sizeof (sml_set_proc_parameter_request));
    memset(msg, 0, sizeof(sml_set_proc_parameter_request));
    return msg;
}

void sml_set_proc_parameter_request_write(sml_set_proc_parameter_request *msg, sml_buffer *buf) {
    sml_buf_set_type_and_length(buf, SML_TYPE_LIST, 5);
    mc_sml_optional_write(buf);
    mc_sml_optional_write(buf);
    mc_sml_optional_write(buf);
    sml_tree_path_write(msg->parameter_tree_path, buf);
    sml_tree_write(msg->parameter_tree, buf);
}

void sml_set_proc_parameter_request_free(sml_set_proc_parameter_request *msg) {
    printf("NYI: %s\n", __FUNCTION__);
}



