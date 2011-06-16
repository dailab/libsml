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


#include <sml/sml_tree.h>
#include <sml/sml_value.h>
#include <stdio.h>

sml_tree_path *sml_tree_path_init() {
    sml_tree_path *tree_path = (sml_tree_path *) malloc(sizeof(sml_tree_path));
    memset(tree_path, 0, sizeof(sml_tree_path));
    return tree_path;
}

void sml_tree_path_add_path_entry(sml_tree_path *tree_path, octet_string *entry) {
    tree_path->path_entries_len++;
    tree_path->path_entries = (octet_string **) realloc(tree_path->path_entries, sizeof(octet_string *) * tree_path->path_entries_len);
    tree_path->path_entries[tree_path->path_entries_len - 1] = entry;
}

void sml_tree_path_write(sml_tree_path *tree_path, sml_buffer *buf) {
    int i;
    if (tree_path->path_entries && tree_path->path_entries_len > 0) {
        mc_sml_set_type_and_length(buf, SML_TYPE_LIST, tree_path->path_entries_len);
        for (i = 0; i < tree_path->path_entries_len; i++) {
            sml_octet_string_write(tree_path->path_entries[i], buf);
        }
    }
}

void sml_tree_path_free(sml_tree_path *tree_path){
	printf("NYI: %s\n", __FUNCTION__);
}


sml_tree *sml_tree_init(octet_string *parameter_name) {
    sml_tree *tree = (sml_tree *) malloc(sizeof(sml_tree));
    memset(tree, 0, sizeof(sml_tree));
    tree->parameter_name = parameter_name;
    return tree;
}

sml_tree *sml_tree_parse(sml_buffer *buf){
	printf("ERROR : NYI sml_tree_parse() not implemented yet");
  return 0;
}

void sml_tree_free(sml_tree *tree){
	printf("ERROR : NYI sml_tree_free() not implemented yet");
}

void sml_tree_write(sml_tree *tree, sml_buffer *buf) {
    mc_sml_set_type_and_length(buf, SML_TYPE_LIST, 3);
    sml_octet_string_write(tree->parameter_name, buf);
    // TODO
    sml_proc_par_value_write(tree->parameter_value, buf);
    //mc_sml_optional_write(buf);
    mc_sml_optional_write(buf);
}

sml_proc_par_value *sml_proc_par_value_init(u8 tag, void *data) {
    
    sml_proc_par_value *value = (sml_proc_par_value *) malloc(sizeof(sml_proc_par_value));
    memset(value, 0, sizeof(sml_proc_par_value));
    value->tag = tag;
    
    switch (tag) {
        case SML_PROC_PAR_VALUE_TAG_VALUE:
            value->data.value = (sml_value*)data;
            break;
        case SML_PROC_PAR_VALUE_TAG_PERIOD_ENTRY:
            printf("TODO: %s\n", __FUNCTION__);
            break;
        case SML_PROC_PAR_VALUE_TAG_TUPEL_ENTRY:
            printf("TODO: %s\n", __FUNCTION__);
            break;
        case SML_PROC_PAR_VALUE_TAG_TIME:
            printf("TODO: %s\n", __FUNCTION__);
            break;
        default:
            if (value) {
                free(value);
            }
            return 0;
    }
    
    return value;
}

void sml_proc_par_value_write(sml_proc_par_value *value, sml_buffer *buf) {
    mc_sml_set_type_and_length(buf, SML_TYPE_LIST, 2);
    sml_number_write(SML_TYPE_UNSIGNED, SML_TYPE_NUMBER_8, (u64) value->tag, buf);

    switch (value->tag) {
        case SML_PROC_PAR_VALUE_TAG_VALUE:
            sml_value_write(value->data.value, buf);
            break;
        case SML_PROC_PAR_VALUE_TAG_PERIOD_ENTRY:
            printf("TODO: %s\n", __FUNCTION__);
            break;
        case SML_PROC_PAR_VALUE_TAG_TUPEL_ENTRY:
            printf("TODO: %s\n", __FUNCTION__);
            break;
        case SML_PROC_PAR_VALUE_TAG_TIME:
            printf("TODO: %s\n", __FUNCTION__);
            break;
        default:
            if (value) {
                free(value);
            }
            buf->error = 1;
    }
}


void sml_proc_par_value_free(sml_proc_par_value *value){
	printf("NYI: %s\n", __FUNCTION__);
}
