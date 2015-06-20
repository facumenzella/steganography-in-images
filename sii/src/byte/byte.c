#include "../../includes/byte.h"

uint8_t
getBit(BYTE byte, uint8_t whichBit)
{
    return (byte >> whichBit) & 0x01;
}

BYTE
overrideLessSignificantBit(BYTE byte, uint8_t bit) {
    return (~1 & byte) | bit;
}
