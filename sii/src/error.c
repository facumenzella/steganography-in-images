#include "../includes/error.h"
#include "../includes/error.h"

void
handleError(error err) {
  if (DEBUGGING) {
    printf("%s\n", err);
  }
}
