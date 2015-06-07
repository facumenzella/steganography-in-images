#ifndef __ERRORS_H__
#define __ERRORS_H__

static const char QTY_ARGS_ERROR[] = "You have to provided the wrong amount of parameters";
static const char MODE_ARG_ERROR[] = "You have to provide either discover or recover mode";
static const char SECRET_ARG_ERROR[] = "You have to provide a secret image";
static const char K_ARG_ERROR[] = "You have to provide a minimum number of shadows";

typedef char* parameters_error;
typedef char* distribution_error;

#endif
