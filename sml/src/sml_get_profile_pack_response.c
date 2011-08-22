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


#include <sml/sml_get_profile_pack_response.h>
#include <stdio.h>

sml_get_profile_pack_response *sml_get_profile_pack_response_init() {
	printf("NYI: %s\n", __FUNCTION__);
	return 0;
}

sml_get_profile_pack_response *sml_get_profile_pack_response_parse(sml_buffer *buf){
	printf("NYI: %s\n", __FUNCTION__);
	return 0;
}

void sml_get_profile_pack_response_write(sml_get_profile_pack_response *msg, sml_buffer *buf) {
	printf("NYI: %s\n", __FUNCTION__);
}

void sml_get_profile_pack_response_free(sml_get_profile_pack_response *msg){
	printf("NYI: %s\n", __FUNCTION__);
}
