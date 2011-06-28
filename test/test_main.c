#include "unity/unity_fixture.h" 

static void runAllTests() {
	RUN_TEST_GROUP(sml_octet_string);
}

int main(int argc, char * argv[]) {
	return UnityMain(argc, argv, runAllTests);
}