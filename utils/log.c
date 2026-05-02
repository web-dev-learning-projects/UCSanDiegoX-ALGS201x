#include "log.h"
#include <stdio.h>
#include <stdarg.h>

void log_with_color(const char *color, const char *statement, ...){
    va_list args;
    va_start(args, statement);
    printf("%s", color);
    vprintf(statement, args);
    printf("%s", RESET);
    va_end(args);
}
