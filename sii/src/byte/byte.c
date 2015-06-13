#include "../../includes/byte.h"

int
getBit(BYTE byte, int whichBit)
{
    if (whichBit > 0 && whichBit <= 8)
        return (byte & (1 << (whichBit - 1)));
    else
        return 0;
}

BYTE
overrideLSB(BYTE byte, int bit) {
  return (~1 & byte) | bit;
}
