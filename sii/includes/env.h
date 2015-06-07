#ifndef __ENV_H__
#define __ENV_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEBUGGING TRUE
#define d_printf(args ...) if (DEBUGGING) fprintf(stderr, args)

#endif
