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
#include <sml/sml_value.h>

TEST_GROUP(sml_value);

sml_buffer *buf;

TEST_SETUP(sml_value) {
	buf = sml_buffer_init(512);
}

TEST_TEAR_DOWN(sml_value) {
	sml_buffer_free(buf);
}

TEST(sml_value, init) {
	sml_value *v = sml_value_init();
	TEST_ASSERT_NOT_NULL(v);
}

TEST(sml_value, parse_octet_string) {
	hex2binary("0648616C6C6F", sml_buf_get_current_buf(buf));
	sml_value *v = sml_value_parse(buf);
	
	TEST_ASSERT_NOT_NULL(v);
	TEST_ASSERT_EQUAL(SML_TYPE_OCTET_STRING, v->type);
	expected_octet_string(v->data.bytes, "Hallo", 5);
}

TEST(sml_value, parse_boolean) {
	hex2binary("4200", sml_buf_get_current_buf(buf));
	sml_value *v = sml_value_parse(buf);

	TEST_ASSERT_NOT_NULL(v);	
	TEST_ASSERT_EQUAL(SML_TYPE_BOOLEAN, v->type);
	TEST_ASSERT_FALSE(*(v->data.boolean));
}

TEST_GROUP_RUNNER(sml_value) {
	RUN_TEST_CASE(sml_value, init);
	RUN_TEST_CASE(sml_value, parse_octet_string);
	RUN_TEST_CASE(sml_value, parse_boolean);
}
