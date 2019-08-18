#include "stdarg.h"
#include "stdio.h"
#include "logging.h"

//printfDebug calls printf, puts [DEBUG] string before the message and \n at end of the line
int printfDebug(const char* message, ...){
    va_list args;
    va_start(args,message);
    printf("[DEBUG] ");
    vprintf(message,args); // TODO: Return printf int
    va_end(args);
    return printf("\n");
}

//printfNone returns 0. Must be used to avoid output messages.
int printfNone(const char* message, ...){
    return 0;
}