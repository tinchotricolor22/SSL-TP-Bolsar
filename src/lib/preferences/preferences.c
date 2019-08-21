#include "preferences.h"
#include "stdlib.h"
#include "../data/data.h"
#include "../parser/parser.h"
#include "../exporter/exporter.h"
#include "../formatter/formatter.h"

ProcessParams* defaultLeaders05VariationScreen(){
    ProcessParams *processParams = malloc(sizeof *processParams);

    processParams->dataMethod = getDataWithOnlineMethod;
    processParams->parserMethod = parseDataFromHTML;
    processParams->exporterMethod = exportStdout;
    processParams->columns = buildLeaderColumns(1,0,0,0,0,0,0);
    processParams->filters = buildLeaderFilters();
    addFilter(processParams->filters,filterMajor05Variation);

    return processParams;
}

ProcessParams* defaultLeaders05VariationHTML(){
    ProcessParams *processParams = malloc(sizeof *processParams);

    processParams->dataMethod = getDataWithOnlineMethod;
    processParams->parserMethod = parseDataFromHTML;
    processParams->exporterMethod = exportHTML;
    processParams->columns = buildLeaderColumns(1,0,0,0,0,0,0);
    processParams->filters = buildLeaderFilters();
    addFilter(processParams->filters,filterMajor05Variation);
    processParams->formatter = buildLeaderFormatter(buildLeaderRedTRCondition);

    return processParams;
}

ProcessParams* defaultLeadersSalePurchaseCSV(){
    ProcessParams *processParams = malloc(sizeof *processParams);

    processParams->dataMethod = getDataWithOnlineMethod;
    processParams->parserMethod = parseDataFromHTML;
    processParams->exporterMethod = exportCSV;
    processParams->columns = buildLeaderColumns(1,1,1,1,1,1,1);
    processParams->filters = buildLeaderFilters();
    addFilter(processParams->filters,filterNoRepeated);

    return processParams;
}

ProcessParams* defaultPreferences(){
    ProcessParams *processParams = malloc(sizeof *processParams);

    processParams->dataMethod = getDataWithFSMethod;//TODO: cambiar a online
    processParams->parserMethod = parseDataFromHTML;
    processParams->exporterMethod = exportCSV;
    processParams->columns = buildLeaderColumns(1,1,1,1,1,1,1);
    processParams->filters = buildLeaderFilters();
    addFilter(processParams->filters,filterNoRepeated);

    return processParams;
}
