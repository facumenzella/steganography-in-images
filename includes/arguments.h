#ifndef __ARGUMENTS_H__
#define __ARGUMENTS_H__

#include <stdio.h>
#include <stdlib.h>

// Parameters structure
typedef struct arguments_t *Arguments;

typedef enum {
    DISTRIBUTE, RECOVER
} mode_type;

Arguments newArguments();

mode_type getMode(Arguments p);
void setMode(Arguments s, mode_type mode);

char *getSecret(Arguments p);
void setSecret(Arguments p, char *secret);

int getMinShadowsToRecoverSecret(Arguments p);
void setMinShadowsToRecoverSecret(Arguments p, int min);

int getTotalAmountOfShadowsToDistributeSecret(Arguments p);
void setTotalAmountOfShadowsToDistributeSecret(Arguments p, int total);

char *getDirectory(Arguments p);
void setDirectory(Arguments p, char *dir);

#endif