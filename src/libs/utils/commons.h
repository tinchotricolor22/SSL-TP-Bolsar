#ifndef COMMONS_HEADER
#define COMMONS_HEADER

void add(void **elems, void *elem, int *length, const int max_length);

void foreach(void **elems, int length, void *(*func)(void *, void *), void *arg2);

void init_list(void **elems, int *length, const int max_length);

void filter(void **elems, int *length, void **elems_filtered, int *length_filtered, int (*condition)(void *));

#endif