
#include "../unity/unity_fixture.h"
#include <sml/sml_octet_string.h>

TEST_GROUP(sml_octet_string);

TEST_SETUP(sml_octet_string) {
	
}

TEST_TEAR_DOWN(sml_octet_string) {
	
}

TEST(sml_octet_string, init) {
	octet_string *str = sml_octet_string_init((unsigned char *)"hallo", 5);
	TEST_ASSERT_TRUE(str->len == 5)
}

TEST_GROUP_RUNNER(sml_octet_string) {
	RUN_TEST_CASE(sml_octet_string, init);
}




