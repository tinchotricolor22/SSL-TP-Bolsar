#ifndef COMMONS_HEADER
#define COMMONS_HEADER

/********* LIST *********/

//add adds element to list of elements.
//increments the length if is minus than max_length
void add(void **elems, void *elem, int *length, const int max_length);

/********* STRINGS *********/
//extract_double_value returns double from string double
double extract_double_value(char *string_double);

//trim quit spaces from string
void trim(const char *input, char *result);

//replace replaces character with replace in input message
void replace(char *input, const char character, const char replace);

//str_replace replace *rep with *with in *orig
char *str_replace(char *orig, char *rep, char *with);

#endif