#ifndef COMMONS_HEADER
#define COMMONS_HEADER

/********* LIST *********/

void add(void **elems, void *elem, int *length, const int max_length);

void foreach(void **elems, int length, void *(*func)(void *, void *), void *arg2);

void init_list(void **elems, int *length, const int max_length);

void filter(void **elems, int *length, void **elems_filtered, int *length_filtered, int (*condition)(void *));

/********* STRINGS *********/
double extractDoubleValue(char* stringDouble);

void trim(const char *input, char *result);

void replace(char *input, const char character, const char replace);

char *str_replace(char *orig, char *rep, char *with);
#endif