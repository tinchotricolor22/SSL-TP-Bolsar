typedef int(*Logger)(const char*,...);

//printfDebug implements function to works in DEBUG mode
int printfDebug(const char*,...);

//printfNone implements function to avoid output messages.
int printfNone(const char*,...);