#ifndef COMMONS_HEADER
#define COMMONS_HEADER

/********* LIST *********/

void add(void **elems, void *elem, int *length, const int max_length);

/********* STRINGS *********/
double extractDoubleValue(char* stringDouble);

void trim(const char *input, char *result);

void replace(char *input, const char character, const char replace);

char *str_replace(char *orig, char *rep, char *with);
#endif