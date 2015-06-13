#ifndef __BYTE_H__
#define __BYTE_H__

typedef unsigned char BYTE;

int getBit(BYTE byte, int whichBit);
BYTE overrideLessSignificantBit(BYTE byte, int bit);

#endif
