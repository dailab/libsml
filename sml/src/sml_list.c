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


#include <sml/sml_list.h>
#include <sml/sml_shared.h>
#include <sml/sml_time.h>
#include <sml/sml_octet_string.h>
#include <sml/sml_status.h>
#include <sml/sml_value.h>
#include <stdio.h>




sml_list *sml_list_init(){
	 sml_list *s = (sml_list *)malloc(sizeof(sml_list));
	 memset(s, 0, sizeof(sml_list));

	 return s;
}

sml_list *sml_list_parse(sml_buffer *buf) {
	int elems, i;
	if (mc_sml_buf_get_current_type(buf) != SML_TYPE_LIST) {
		buf->error = 1;
		return 0;
	}
	
	elems = sml_buf_get_next_length(buf);
	sml_list *start = 0;
	sml_list *cur = 0;
	sml_list *tmp;
	
	for (i = 0; i < elems; i++) {
		
		if (mc_sml_buf_get_current_type(buf) != SML_TYPE_LIST) {
			buf->error = 1;
			goto error;
		}
		
		if (sml_buf_get_next_length(buf) != 7) {
			buf->error = 1;
			goto error;
		}
		
		tmp = (sml_list *) malloc(sizeof(sml_list));
		if (i == 0) {
			start = tmp;
			cur = tmp;
		}
		else {
			cur->next = tmp;
			cur = tmp;
		}

		cur->obj_name = sml_octet_string_parse(buf);
		if (sml_buf_has_errors(buf)) goto error;
		
		cur->status = SML_SKIP_OPTIONAL sml_status_parse(buf);
		if (sml_buf_has_errors(buf)) goto error;
		
		cur->val_time = SML_SKIP_OPTIONAL sml_time_parse(buf);
		if (sml_buf_has_errors(buf)) goto error;
		
		cur->unit = SML_SKIP_OPTIONAL mc_sml_parse_u8(buf);
		if (sml_buf_has_errors(buf)) goto error;

		cur->scaler = SML_SKIP_OPTIONAL mc_sml_parse_i8(buf);
		if (sml_buf_has_errors(buf)) goto error;

		cur->value = SML_SKIP_OPTIONAL sml_value_parse(buf);
		if (sml_buf_has_errors(buf)) goto error;

		cur->value_signature = SML_SKIP_OPTIONAL sml_octet_string_parse(buf);
		if (sml_buf_has_errors(buf)) goto error;
		
		cur->next = 0;
	}
	return start;
	
error:
	buf->error = 1;
	return 0;
}

void sml_list_write(sml_list *list, sml_buffer *buf){
    sml_buf_set_type_and_length(buf, SML_TYPE_LIST, 1);
    mc_sml_optional_write(buf);
   //
}

void sml_list_entry_free(sml_list *list) {
    if (list) {
        sml_octet_string_free(list->obj_name);
        sml_status_free(list->status);
        sml_time_free(list->val_time);
        sml_value_free(list->value);
        sml_octet_string_free(list->value_signature);
        free(list);
    }
}

void sml_list_free(sml_list *list) {
    if (list) {
        sml_list *f = list;
        sml_list *n = list->next;
        
        while(f) {
            sml_list_entry_free(f);
            f = n;
            if (f) {
                n = f->next;
            }
        }
    }
}
