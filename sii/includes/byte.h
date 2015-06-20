#ifndef __BYTE_H__
#define __BYTE_H__

#include <inttypes.h>

typedef unsigned char BYTE;

int getBit(BYTE byte, uint8_t whichBit);
BYTE overrideLessSignificantBit(BYTE byte, uint8_t bit);

#endif
