#ifndef FILTER_HEADER
#define FILTER_HEADER

#include "parsertypes.h" //Cambiar

#define FILTER_RESULT_OK 0
#define FILTER_RESULT_ERROR 1
#define NO_FILTERS_APPLIED 2

typedef int FilterResult;

typedef ParserOutput FilterOutput;

typedef FilterResult(*Filter)(void *data, void **filteredData);

typedef struct Filters {
    Filter **filter_list;
    int filter_list_length;
} Filters;

FilterResult filterMajor05Variation(ParserOutput *data, ParserOutput **filteredData);
FilterResult filterNoRepeated(ParserOutput *data, FilterOutput **filteredData); //TODO: Parche provisorio

int major05Variation(Leader *leader);

int noRepeated(Leader *leader);
Filters *buildLeaderFilters();
FilterOutput *buildFilterOutput();
void addFilter(Filters* filters, Filter *filter);

#endif