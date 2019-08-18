#ifndef COMMONS_HEADER
#define COMMONS_HEADER

void add(void **elems, void *elem, int *length, const int max_length);
void foreach(void **elems, int length, void*(*func)(void*,void*), void* arg2);
void init_list(void **elems, int *length, const int max_length);

#endif