#include "../../includes/errors.h"

void
setError(char **err, const char msg[]) {
  *err = calloc(strlen(msg) + 1, sizeof(char));
  strcpy(*err, msg);
}
