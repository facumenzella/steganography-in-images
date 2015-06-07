#include "../includes/errors.h"

void
handleError(error err) {
  if (DEBUGGING) {
    printf("%s\n", err);
  }
}
