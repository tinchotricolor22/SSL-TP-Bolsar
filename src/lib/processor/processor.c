#include "processor.h"
#include "../exporter/exportertypes.h"
#include "../filter/filter.h"
#include "stdio.h"
#include "stdlib.h"

Logger processorDebugLogger;

void initProcessor(Logger processorDebugLoggerArg) {
    processorDebugLogger = processorDebugLoggerArg;
}

void
initProcessParams(DataMethod dataMethod, ParserMethod parserMethod, ExporterMethod exporterMethod, Filters *filters,
                  Formatter **formatter, ExporterColumns **columns) {
    processParams = malloc(sizeof *processParams);
    processParams->dataMethod = dataMethod;
    processParams->parserMethod = parserMethod;
    processParams->exporterMethod = exporterMethod;
    processParams->filters = filters;
    processParams->formatter = *formatter;
    processParams->columns = *columns;
}

ProcessResult process() {
    processorDebugLogger("Calling dataMethod [event:process]");

    DataOutput *dataData;
    DataResult resultData = processParams->dataMethod(&dataData);

    if (resultData != DATA_RESULT_OK) {
        return PROCESS_ERROR_DATA;
    }

    processorDebugLogger("Calling parserMethod [event:process]");

    ParserInput *parserInput = buildParserInputFromDataOutput(dataData);
    ParserOutput *parserData;
    ParserResult resultParser = processParams->parserMethod(&parserData, parserInput);

    if (resultParser != PARSER_RESULT_OK) {
        return PROCESS_ERROR_PARSER;
    }

    processorDebugLogger("Calling filters [event:process]");
    FilterOutput *filteredData = buildFilterOutput();
    FilterResult resultFilter = executeFilters(parserData, &filteredData);

    FilterOutput **exporterData = &filteredData;
    if (resultFilter == NO_FILTERS_APPLIED) {
        exporterData = &parserData;
    } else if (resultFilter != FILTER_RESULT_OK) {
        return PROCESS_ERROR_FILTER;
    }

    processorDebugLogger("Calling exportMethod [event:process]");
    ExporterParams *exporterParams = buildExporterParams();
    ExportResult resultExport = processParams->exporterMethod(*exporterData, exporterParams);

    if (resultExport != EXPORT_RESULT_OK) {
        return PROCESS_ERROR_EXPORTER;
    }

    closeResources(dataData);

    return PROCESS_OK;
}

ExporterParams *buildExporterParams() {
    ExporterParams *ep = malloc(sizeof *ep);
    ep->columns = processParams->columns;
    ep->formatter = processParams->formatter;

    return ep;
}

FilterResult executeFilters(ParserOutput *data, FilterOutput **filteredData) {
    if (processParams->filters != NULL) {
        for (int i = 0; i < processParams->filters->filter_list_length; i++) {

            Filter execFilter = processParams->filters->filter_list[i];
            FilterResult result = execFilter(data, filteredData);
            if (result != FILTER_RESULT_OK) {
                return result;
            }
        }
    } else {
        return NO_FILTERS_APPLIED;
    }
    return FILTER_RESULT_OK;
}

void closeResources(DataOutput *dataData) {
    fclose(dataData->file);
}
//TODO: CLOSE ALL FILES