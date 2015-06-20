#include "../../includes/byte.h"

int
getBit(BYTE byte, uint8_t whichBit)
{
    return (byte >> whichBit) & 0x01;
}

BYTE
overrideLessSignificantBit(BYTE byte, uint8_t bit) {
    return (~1 & byte) | bit;
}
