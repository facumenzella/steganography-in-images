#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include "byte.h"

#define MAX_BYTE_VALUE 251

#ifndef BOOLEAN
typedef int boolean;
#define TRUE 1
#define FALSE !TRUE
#endif

#define EXIT exit(-1)

#endif
