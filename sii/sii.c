#include "./includes/sii.h"
#include "./includes/imageUtils.h"

static const char DISTRIBUTE_WELCOME_MSG[] = "You have chosen Distribution mode...";
static const char RECOVER_WELCOME_MSG[] = "You have chosen Recover mode...";

void handleErrorIfNeeded(arguments_error error);

int
main(int argc, char * argv[]) {

  arguments_error error;
  Arguments arguments = validateArguments(argc, argv, &error);

  handleErrorIfNeeded(error);

  main_error err;
  switch (getMode(arguments)) {
    case DISTRIBUTE:
    printf("%s\n", DISTRIBUTE_WELCOME_MSG);
    distribute(arguments, &err);
    break;
    case RECOVER:
    printf("%s\n", RECOVER_WELCOME_MSG);
    break;
  }
}


void
handleErrorIfNeeded(arguments_error error) {
  if (error != NULL) {
    d_printf("%s\n", error);
    EXIT;
  }
}
