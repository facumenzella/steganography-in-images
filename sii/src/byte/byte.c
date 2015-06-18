#include "../../includes/byte.h"

int
getBit(BYTE byte, int whichBit)
{
    return (byte >> whichBit) & 0x01;
}

BYTE
overrideLessSignificantBit(BYTE byte, int bit) {
    return (~1 & byte) | bit;
}
