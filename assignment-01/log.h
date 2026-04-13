#include <stdio.h>
#include <stdarg.h>

#define  GREEN          "\033[0;32m"
#define  YELLOW         "\033[0;33m"
#define  BLUE           "\033[0;34m"
#define  MAGENTA        "\033[0;35m"
#define  CYAN           "\033[0;36m"
#define  BRIGHT_GREEN   "\033[1;32m"
#define  BRIGHT_YELLOW  "\033[1;33m"
#define  BRIGHT_BLUE    "\033[1;34m"
#define  BRIGHT_MAGENTA "\033[1;35m"
#define  BRIGHT_CYAN    "\033[1;36m"
#define  RED            "\033[0;31m"
#define  BRIGHT_RED     "\033[1;31m"
#define  WHITE          "\033[0;37m"
#define  BRIGHT_WHITE   "\033[1;37m"
#define  LIGHT_RED      "\033[0;91m"
#define  LIGHT_GREEN    "\033[0;92m"
#define  LIGHT_YELLOW   "\033[0;93m"
#define  LIGHT_BLUE     "\033[0;94m"
#define  LIGHT_MAGENTA  "\033[0;95m"
#define  LIGHT_CYAN     "\033[0;96m"
#define  RESET          "\033[0m"

void log_with_color(const char *color, const char *statement, ...){
    va_list args;
    va_start(args, statement);
    printf("%s", color);
    vprintf(statement, args);
    printf("%s", RESET);
    va_end(args);
}