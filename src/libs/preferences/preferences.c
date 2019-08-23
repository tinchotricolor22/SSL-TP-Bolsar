#include "preferences.h"
#include "stdlib.h"
#include "../utils/commons.h"
#include "../data/data.h"
#include "../parser/parser.h"
#include "../exporter/exporter.h"
#include "../formatter/formatter.h"

ProcessParams *defaultLeaders05VariationScreen() {
    ProcessParams *processParams = malloc(sizeof *processParams);

    processParams->dataMethod = getDataWithOnlineMethod;
    processParams->parserMethod = parseDataFromHTML;
    processParams->exporterMethod = exportStdout;
    processParams->columns = buildLeaderColumns(1, 0, 0, 0, 0, 0, 0);
    processParams->filters = malloc(sizeof processParams->filters[0] * FILTERS_MAX_LENGTH);
    processParams->filters_length = 0;
    add(processParams->filters, leader_filter_major_05_variation, &processParams->filters_length, FILTERS_MAX_LENGTH);

    processParams->formats_conditions_length = 0;

    return processParams;
}

ProcessParams *defaultLeaders05VariationHTML() {
    ProcessParams *processParams = malloc(sizeof *processParams);

    processParams->dataMethod = getDataWithOnlineMethod;
    processParams->parserMethod = parseDataFromHTML;
    processParams->exporterMethod = exportHTML;
    processParams->columns = buildLeaderColumns(1, 0, 0, 0, 0, 0, 0);

    processParams->filters = malloc(sizeof processParams->filters[0] * FILTERS_MAX_LENGTH);
    processParams->filters_length = 0;
    add(processParams->filters, leader_filter_major_05_variation, &processParams->filters_length, FILTERS_MAX_LENGTH);

    processParams->formats_conditions = malloc(sizeof processParams->formats_conditions[0] * MAX_FORMATS);
    processParams->formats_conditions_length = 0;
    add(processParams->formats_conditions, leader_purchase_sale_major_opening, &processParams->formats_conditions_length, MAX_FORMATS);

    return processParams;
}

ProcessParams *defaultLeadersSalePurchaseCSV() {
    ProcessParams *processParams = malloc(sizeof *processParams);

    processParams->dataMethod = getDataWithOnlineMethod;
    processParams->parserMethod = parseDataFromHTML;
    processParams->exporterMethod = exportCSV;
    processParams->columns = buildLeaderColumns(1, 1, 1, 1, 1, 1, 1);
    processParams->filters_length = 0;
    processParams->formats_conditions_length = 0;

    return processParams;
}

ProcessParams *defaultPreferences() {
    ProcessParams *processParams = malloc(sizeof *processParams);

    processParams->dataMethod = getDataWithFSMethod;
    processParams->parserMethod = parseDataFromHTML;
    processParams->exporterMethod = exportCSV;
    processParams->columns = buildLeaderColumns(1, 1, 1, 1, 1, 1, 1);
    processParams->filters_length = 0;
    processParams->formats_conditions_length = 0;

    return processParams;
}
