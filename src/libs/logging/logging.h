#ifndef LOGGING_HEADER
#define LOGGING_HEADER

//Logger represents function that logs messages
typedef int(*Logger)(const char *, ...);

//printf_debug implements function to works in DEBUG mode
int printf_debug(const char *, ...);

//printf_none returns 0. Must be used to avoid output messages.
int printf_none(const char *, ...);

#endif