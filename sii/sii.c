#include "./includes/sii.h"
#include "./includes/imageUtils.h"

static const char DISTRIBUTE_WELCOME_MSG[] = "You have chosen Distribution mode...";
static const char RECOVER_WELCOME_MSG[] = "You have chosen Recover mode...";

void handleErrorIfNeeded(char *error);

int
main(int argc, char * argv[]) {
    
    arguments_error error;
    Arguments arguments = validateArguments(argc, argv, &error);
    
    handleErrorIfNeeded((char*)error);
    
    main_error err = NULL;
    switch (getMode(arguments)) {
        case DISTRIBUTE:
            printf("%s\n", DISTRIBUTE_WELCOME_MSG);
            runDistribution(arguments, &err);
            break;
        case RECOVER:
            printf("%s\n", RECOVER_WELCOME_MSG);
            runReveal(arguments, &err);
            break;
    }
    handleErrorIfNeeded((char*)err);
}

void
handleErrorIfNeeded(char * error) {
    if (error != NULL) {
        printf("%s\n", error);
        EXIT;
    }
}
