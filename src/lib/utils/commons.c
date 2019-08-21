#include "commons.h"
#include "stdlib.h"
#include "../formatter/formattertypes.h"
#include "../domain/leader.h"//BORRAR
#include "string.h"//BORRAR

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