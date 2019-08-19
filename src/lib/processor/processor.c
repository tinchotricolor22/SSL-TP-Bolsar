#include "processor.h"
#include "../parser/parsertypes.h"
#include "../exporter/exportertypes.h"
#include "../filter/filter.h"
#include "stdlib.h"

Logger processorDebugLogger;

void initProcessor(Logger processorDebugLoggerArg) {
    processorDebugLogger = processorDebugLoggerArg;
}

void initProcessParams(ParserMethod parserMethod, ExporterMethod exporterMethod, Filters *filters,
                       Formatter **formatter, ExporterColumns **columns) {
    processParams = malloc(sizeof *processParams);
    processParams->parserMethod = parserMethod;
    processParams->exporterMethod = exporterMethod;
    processParams->filters = filters;
    processParams->formatter = *formatter;
    processParams->columns = *columns;
}

ProcessResult process() {
    processorDebugLogger("Calling parserMethod [event:process]");
    Data *data;
    ParserResult resultParser = processParams->parserMethod(&data);

    if (resultParser != PARSER_RESULT_OK) {
        return PROCESS_ERROR_PARSER;
    }

    processorDebugLogger("Calling filters [event:process]");
    Data *filteredData = malloc(sizeof *filteredData);
    FilterResult resultFilter = executeFilters(data, &filteredData);

    if (resultFilter != FILTER_RESULT_OK) {
        return PROCESS_ERROR_FILTER;
    }

    processorDebugLogger("Calling exportMethod [event:process]");
    ExporterParams *exporterParams = buildExporterParams();
    ExportResult resultExport = processParams->exporterMethod(&filteredData, exporterParams);

    if (resultExport != EXPORT_RESULT_OK) {
        return PROCESS_ERROR_EXPORTER;
    }

    return PROCESS_OK;
}

ExporterParams *buildExporterParams() {
    ExporterParams *ep = malloc(sizeof *ep);
    ep->columns = processParams->columns;
    ep->formatter = processParams->formatter;

    return ep;
}

FilterResult executeFilters(Data *data, Data *filteredData) {
    for (int i = 0; i < processParams->filters->filter_list_length; i++) {

        Filter execFilter = processParams->filters->filter_list[i];
        FilterResult result = execFilter(data, filteredData);
        if (result != FILTER_RESULT_OK) {
            return result;
        }
    }
    return FILTER_RESULT_OK;
}