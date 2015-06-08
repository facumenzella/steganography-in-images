#include "../../includes/random.h"

double randnormalize(void);
void randomize(int num);

long int
getRandom(long int max) {
  return (long int) (randnormalize()*(max + 1)); /*devuelve un número en [0,max]*/
}

double
randnormalize(void) {
  return rand()/((double)RAND_MAX+1);
}

void
randomize(int num) {
  srand((int) num);
}
