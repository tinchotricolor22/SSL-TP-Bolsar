#include "stdarg.h"
#include "stdio.h"
#include "logging.h"

int printf_debug(const char *message, ...) {
    va_list args;
    va_start(args, message);
    printf("[DEBUG] ");
    vprintf(message, args);
    va_end(args);
    return printf("\n");
}

int printf_none(const char *message, ...) {
    return 0;
}