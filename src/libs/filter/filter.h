#ifndef FILTER_HEADER
#define FILTER_HEADER

#include "leader.h"

#define FILTERS_MAX_LENGTH 2

//FilterResult represents the result of filter methods
typedef int FilterResult;

//Filter represents the filter method
typedef FilterResult(*Filter)(const void *data);

//_leader_filter_major_05_variation is a filter that returns true if leader has variation > 0.5
FilterResult _leader_filter_major_05_variation(const Leader *);

#endif