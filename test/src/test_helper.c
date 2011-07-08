
#include "test_helper.h"
#include <stdint.h>
#include <string.h>

uint8_t test_helper_ctoi(uint8_t c){
    uint8_t ret = 0;
    
    if((c >= '0') && (c <= '9')){
        ret = c - '0';
    } else if((c >= 'a') && (c <= 'f')){
        ret = c - 'a' + 10;
    } else if((c >= 'A') && (c <= 'F')){
        ret = c - 'A' + 10;
    }
    
    return ret;
}

inline uint8_t test_helper_c2toi(uint8_t c1, uint8_t c2){
    return test_helper_ctoi(c1) << 4 | test_helper_ctoi(c2);
}

inline uint8_t test_helper_c2ptoi(char* c){
    return test_helper_ctoi((uint8_t)c[0]) << 4 | test_helper_ctoi((uint8_t)c[1]);
}

int hex2binary(char *hex, unsigned char *buf) {
	int i;
	int len = strlen(hex);
	for (i = 0; i < (len /2); i++) {
		buf[i] = test_helper_c2ptoi(&(hex[i * 2]));
	}
	return i;
}

