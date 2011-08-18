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
#include <sml/sml_tree.h>

TEST_GROUP(sml_tree);

sml_buffer *buf;

TEST_SETUP(sml_tree) {
	buf = sml_buffer_init(512);
}

TEST_TEAR_DOWN(sml_tree) {
	sml_buffer_free(buf);
}

TEST(sml_tree, init) {
	sml_tree *t = sml_tree_init();
	TEST_ASSERT_NOT_NULL(t);
}

TEST_GROUP_RUNNER(sml_tree) {
	RUN_TEST_CASE(sml_tree, init);
}




TEST_GROUP(sml_proc_par_value);

TEST_SETUP(sml_proc_par_value) {
	buf = sml_buffer_init(512);
}

TEST_TEAR_DOWN(sml_proc_par_value) {
	sml_buffer_free(buf);
}

TEST(sml_proc_par_value, init) {
	sml_proc_par_value *t = sml_proc_par_value_init();
	TEST_ASSERT_NOT_NULL(t);
}

TEST(sml_proc_par_value, parse_time) {
	hex2binary("72620472620265000000FF", sml_buf_get_current_buf(buf));
	sml_proc_par_value *t = sml_proc_par_value_parse(buf);
	TEST_ASSERT_NOT_NULL(t);
	TEST_ASSERT_EQUAL(SML_PROC_PAR_VALUE_TAG_TIME, *(t->tag));
}

TEST_GROUP_RUNNER(sml_proc_par_value) {
	RUN_TEST_CASE(sml_proc_par_value, init);
	RUN_TEST_CASE(sml_proc_par_value, parse_time);
}

