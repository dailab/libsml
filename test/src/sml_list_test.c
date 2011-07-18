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

#include "../unity/unity_fixture.h"
#include "test_helper.h"
#include <sml/sml_list.h>

TEST_GROUP(sml_list);

sml_buffer *buf;

TEST_SETUP(sml_list) {
	buf = sml_buffer_init(512);
}

TEST_TEAR_DOWN(sml_list) {
	sml_buffer_free(buf);
}

TEST(sml_list, init) {
	sml_list *v = sml_list_init();
	TEST_ASSERT_NOT_NULL(v);
}

TEST_GROUP_RUNNER(sml_list) {
	RUN_TEST_CASE(sml_list, init);
}
