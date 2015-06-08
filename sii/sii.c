#include "./includes/sii.h"

static const char DISTRIBUTE_WELCOME_MSG[] = "You have chosen Distribution mode...";
static const char RECOVER_WELCOME_MSG[] = "You have chosen Recover mode...";

void handleErrorIfNeeded(parameters_error error);

int
main(int argc, char * argv[]) {

  parameters_error error;
  Parameters parameters = validateParameters(argc, argv, &error);

  handleErrorIfNeeded(error);

  main_error err;
  switch (getMode(parameters)) {
    case DISTRIBUTE:
    d_printf("%s\n", DISTRIBUTE_WELCOME_MSG);
    distribute(parameters, &err);
    break;
    case RECOVER:
    d_printf("%s\n", RECOVER_WELCOME_MSG);
    break;
  }

}


void
handleErrorIfNeeded(parameters_error error) {
  if (error) {
    d_printf("%s\n", error);
    EXIT;
  }
}
