#ifndef SML_CRC16_H_
#define SML_CRC16_H_

#include "sml_shared.h"

#ifdef __cplusplus
extern "C" {
#endif


// CRC16 FSC implementation based on DIN 62056-46
u16 sml_crc16_calculate(unsigned char *cp, int len) ;

#ifdef __cplusplus
}
#endif


#endif /* SML_CRC16_H_ */



