
#include "../unity/unity_fixture.h"
#include <sml/sml_shared.h>

TEST_GROUP(sml_buffer);

int buffer_len = 512;
sml_buffer *buf;

TEST_SETUP(sml_buffer) {
	buf = sml_buffer_init(buffer_len);
}

TEST_TEAR_DOWN(sml_buffer) {
	
}

TEST(sml_buffer, init_defaults) {
	
	TEST_ASSERT_NOT_NULL(buf);
	TEST_ASSERT_NOT_NULL(buf->buffer);
	TEST_ASSERT_EQUAL(buffer_len, buf->buffer_len);
	TEST_ASSERT_EQUAL(0, buf->cursor);
	TEST_ASSERT_EQUAL(0, buf->error);
	TEST_ASSERT_NULL(buf->error_msg);
}

TEST_GROUP_RUNNER(sml_buffer) {
	RUN_TEST_CASE(sml_buffer, init_defaults);
}




