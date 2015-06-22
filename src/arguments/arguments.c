#include "../../includes/arguments.h"

#define MODE(m) (m == DISTRIBUTE) ? "distribute" : "recover"

typedef struct arguments_t {
    mode_type mode;
    char *secret;
    int minShadowsToRecoverSecret;
    int totalAmountOfShadowsToDistributeSecret;
    char *directory;
} parameters_t;


Arguments newArguments() {
    Arguments arguments = malloc(sizeof(struct arguments_t));
    arguments->minShadowsToRecoverSecret = -1;
    arguments->totalAmountOfShadowsToDistributeSecret = -1;
    return arguments;
}

mode_type
getMode(Arguments p) {
    return p->mode;
}

void
setMode(Arguments s, mode_type mode) {
    s->mode = mode;
//    printf("Setting mode to %s\n", MODE(mode));
}

char *getSecret(Arguments p) {
    return p->secret;
}

void
setSecret(Arguments p, char *secret) {
    p->secret = secret;
//    printf("Setting secret to %s\n", secret);
}

int getMinShadowsToRecoverSecret(Arguments p) {
    return p->minShadowsToRecoverSecret;
}

void
setMinShadowsToRecoverSecret(Arguments p, int min) {
    p->minShadowsToRecoverSecret = min;
//    printf("Setting Min shadows(k) to %d\n", min);
}


int getTotalAmountOfShadowsToDistributeSecret(Arguments p) {
    return p->totalAmountOfShadowsToDistributeSecret;
}

void
setTotalAmountOfShadowsToDistributeSecret(Arguments p, int total) {
    p->totalAmountOfShadowsToDistributeSecret = total;
//    printf("Setting Total amount of shadows(n) to %d\n", total);
}

char *getDirectory(Arguments p) {
    return p->directory;
}

void
setDirectory(Arguments p, char *dir) {
    p->directory = dir;
//    printf("Setting directory %s\n", dir);
}

