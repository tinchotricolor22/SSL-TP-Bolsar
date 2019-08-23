#include "commons.h"
#include "stdlib.h"
#include "../formatter/formattertypes.h"
#include "string.h"
#include "ctype.h"

void add(void **elems, void *elem, int *length, const int max_length) {
    if (*length < max_length) {
        elems[(*length)++] = elem;
    }
}

void foreach(void **elems, int length, void *(*func)(void *, void *), void *arg2) {
    for (int i = 0; i < length; i++) {
        func(arg2, elems[i]);
    }
}

void init_list(void **elems, int *length, const int max_length) {
    elems = malloc(max_length * sizeof elems[0]);
    *length = 0;
}

void filter(void **elems, int *length, void **elems_filtered, int *length_filtered, int (*condition)(void *)) {
    init_list(elems_filtered, length_filtered, *length);

    for (int i = 0; i < *length; i++) {
        if (condition(elems[i])) {
            add(elems_filtered, elems[i], length_filtered, *length);
        }
    }
}


double extractDoubleValue(char *stringDouble) {
    trim(stringDouble, stringDouble);
    replace(stringDouble, ',', '.');

    return atof(stringDouble);
}

void trim(const char *input, char *result) {
    int i, j = 0;
    for (i = 0; input[i] != '\0'; i++) {
        if (!isspace((unsigned char) input[i])) {
            result[j++] = input[i];
        }
    }
    result[j] = '\0';
}

void replace(char *input, const char character, const char replace) {
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == character) {
            input[i] = replace;
        }
    }
}

// You must free the result if result is non-NULL.
char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}