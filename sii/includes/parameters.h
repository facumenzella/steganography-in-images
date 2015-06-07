#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

#define MIN 3
#define MAX 5

typedef enum {
  DISTRIBUTE, RECOVER
} mode_type;

typedef char* parameters_error;


// functions
void validateParaemeters(int argc, char * argv[], mode_type *m, parameters_error *error);

#endif
