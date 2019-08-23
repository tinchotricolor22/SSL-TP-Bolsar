#ifndef FILTER_HEADER
#define FILTER_HEADER

#include "leader.h"

#define FILTERS_MAX_LENGTH 2

typedef int FilterResult;
typedef FilterResult(*Filter)(void *data);

FilterResult leader_filter_major_05_variation(Leader *leader);

#endif