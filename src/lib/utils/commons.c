#include "commons.h"
#include "../formatter/formattertypes.h"

void add(void **elems, void *elem, int *length, const int max_length){
    if (*length < max_length){
        elems[(*length)++] = elem;
    }
}

void foreach(void **elems, int length, void*(*func)(void*,void*), void* arg2){
    for(int i = 0 ; i<length; i++){
        printf("viendo el componente en el foreach: %s\n",((Format*) elems[i])->apply_component);
        printf("viendo el componente en el foreach: %s\n",((Format*) elems[i])->identifier);
        printf("viendo el componente en el foreach: %s\n",((Format*) elems[i])->value);
        func(arg2,elems[i]);
    }
}

void init_list(void **elems, int *length, const int max_length){
    printf("en init_list\n");

    elems = malloc(max_length * sizeof elems[0]);
    *length = 0;
}