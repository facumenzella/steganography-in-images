#include "./includes/sii.h"

static const char DISTRIBUTE_WELCOME_MSG[] = "You have chosen Distribution mode...";
static const char RECOVER_WELCOME_MSG[] = "You have chosen Recover mode...";

int handleErrorIfNeeded(parameters_error error);

int
main(int argc, char * argv[]) {

  parameters_error error = calloc(1024, sizeof(char));
  Parameters parameters = validateParameters(argc, argv, &error);

  handleErrorIfNeeded(error);

  switch (getMode(parameters)) {
    case DISTRIBUTE:
    d_printf("%s\n", DISTRIBUTE_WELCOME_MSG);
    distribute(parameters);
    break;
    case RECOVER:
    d_printf("%s\n", RECOVER_WELCOME_MSG);

    break;
  }

}


int
handleErrorIfNeeded(parameters_error error) {
  d_printf("%s\n", error);
  if (error) {
    return -1;
  }
  return 0;
}
