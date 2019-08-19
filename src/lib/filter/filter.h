#ifndef FILTER_HEADER
#define FILTER_HEADER

#include "parsertypes.h" //Cambiar

#define FILTER_RESULT_OK 0
#define FILTER_RESULT_ERROR 1
typedef int FilterResult;

typedef ParserOutput FilterOutput;

typedef FilterResult(*Filter)(void *data, void *filteredData);

typedef struct Filters {
    Filter **filter_list;
    int filter_list_length;
} Filters;

FilterResult filterMajor05Variation(ParserOutput *data, ParserOutput *filteredData);

int major05Variation(Leader *leader);

Filters *buildLeaderFilters(Filter *filter);

#endif