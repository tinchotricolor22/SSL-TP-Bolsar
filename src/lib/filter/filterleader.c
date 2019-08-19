#include "filter.h"
#include "stdlib.h"
#include "../utils/commons.h"
#include "../domain/leader.h"

#define FILTERS_LEADERS 1

FilterResult filterMajor05Variation(ParserOutput *data, FilterOutput *filteredData) {
    filter(data->leaders, &(data->leaders_length), filteredData->leaders, &(filteredData->leaders_length),
           major05Variation);
    return FILTER_RESULT_OK;
}

int major05Variation(Leader *leader) {
    return leader->variation > 0.5;
}

Filters *buildLeaderFilters() {
    Filter **filter_list = malloc(sizeof **filter_list * FILTERS_LEADERS); //probar init_list
    Filters *filters = malloc(sizeof *filter);
    filters->filter_list = filter_list;
    filters->filter_list_length = 0;
    add(filters->filter_list, filterMajor05Variation, &(filters->filter_list_length), FILTERS_LEADERS);
    return filters;
}