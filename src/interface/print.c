#include "../def.h"

void I_Error(const char *output, ...)
{
    va_list args;

    printf("error: ");

    va_start(args, output);
    vprintf(output, args);
    va_end(args);

    printf("\n");

    exit(EXIT_FAILURE);
}
