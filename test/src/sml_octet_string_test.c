
#include "../unity/unity_fixture.h"
#include "test_helper.h"
#include <sml/sml_octet_string.h>

TEST_GROUP(sml_octet_string);

sml_buffer *buf;
void expected_octet_string(octet_string *str, char *content, int len) {
	TEST_ASSERT_NOT_NULL(str);
	TEST_ASSERT_EQUAL(len, str->len);
	TEST_ASSERT_EQUAL_MEMORY(content, str->str, len);
}

TEST_SETUP(sml_octet_string) {
	buf = sml_buffer_init(512);
}

TEST_TEAR_DOWN(sml_octet_string) {
	
}

TEST(sml_octet_string, init) {
	octet_string *str = sml_octet_string_init((unsigned char *)"hallo", 5);
	TEST_ASSERT_EQUAL(5, str->len);
	TEST_ASSERT_EQUAL_MEMORY("hallo", str->str, 5);
}

TEST(sml_octet_string, parse) {
	hex2binary("0648616C6C6F", sml_buf_get_current_buf(buf));
	
	octet_string *str = sml_octet_string_parse(buf);
	expected_octet_string(str, "Hallo", 5);
}

TEST(sml_octet_string, parse_multiple_tl_fields) {
	hex2binary("8102616161616F6161616161616161616161", sml_buf_get_current_buf(buf));
	
	octet_string *str = sml_octet_string_parse(buf);
	expected_octet_string(str, "aaaaoaaaaaaaaaaa", 16);
}

TEST_GROUP_RUNNER(sml_octet_string) {
	RUN_TEST_CASE(sml_octet_string, init);
	RUN_TEST_CASE(sml_octet_string, parse);
	RUN_TEST_CASE(sml_octet_string, parse_multiple_tl_fields);
}




