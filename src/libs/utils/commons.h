#ifndef COMMONS_HEADER
#define COMMONS_HEADER

/********* LIST *********/

//add adds element to list of elements.
//increments the length if is minus than max_length
void add(void **, void *, int *, const int);

/********* STRINGS *********/
//extract_double_value returns double from string double
double extract_double_value(char *);

//trim quit spaces from string
void trim(const char *, char *);

//replace replaces character with replace in input message
void replace(char *, const char, const char);

//str_replace replace *rep with *with in *orig
char *str_replace(char *, char *, char *);

#endif