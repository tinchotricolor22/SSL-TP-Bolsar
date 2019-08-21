#include "filter.h"
#include "stdlib.h"
#include "../utils/commons.h"
#include "../domain/leader.h"

#define FILTERS_LEADERS 1

FilterResult filterMajor05Variation(ParserOutput *data, FilterOutput **filteredData) {
    filter(data->leaders, &(data->leaders_length), (*filteredData)->leaders, &((*filteredData)->leaders_length),
           major05Variation);
    return FILTER_RESULT_OK;
}

FilterResult filterNoRepeated(ParserOutput *data, FilterOutput **filteredData) {
    filter(data->leaders, &(data->leaders_length), (*filteredData)->leaders, &((*filteredData)->leaders_length),
           noRepeated);
    return FILTER_RESULT_OK;
}

int major05Variation(Leader *leader) {
    return leader->variation > 0.5;
}

int noRepeated(Leader *leader) { //TODO: PARCHE PROVISORIO
    return leader->variation > 0 || leader->purchasePrice > 0 || leader->salePrice > 0 ||
           leader->openingPrice > 0 || leader->maxPrice > 0  || leader->minPrice > 0;
}

Filters *buildLeaderFilters() {
    Filter **filter_list = malloc(sizeof **filter_list * FILTERS_LEADERS); //probar init_list
    Filters *filters = malloc(sizeof *filters);
    filters->filter_list = filter_list;
    filters->filter_list_length = 0;

    return filters;
}

void addFilter(Filters* filters, Filter *filter) {
    add(filters->filter_list, filter, &(filters->filter_list_length), FILTERS_LEADERS);
}

FilterOutput *buildFilterOutput() {
    Leader **leaders = malloc(sizeof **leaders * LEADERS_MAX_LENGTH);
    FilterOutput *filterOutput = malloc(sizeof *filterOutput);
    filterOutput->leaders = leaders;
    filterOutput->leaders_length = 0;

    return filterOutput;
}