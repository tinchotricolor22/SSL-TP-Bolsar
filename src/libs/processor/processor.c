#include "processor.h"
#include "../exporter/exportertypes.h"
#include "../filter/filter.h"
#include "stdio.h"
#include "stdlib.h"

Logger processorDebugLogger;

ParserInput *buildParserInput(DataOutput *dataOutput);


void initProcessor(Logger processorDebugLoggerArg) {
    processorDebugLogger = processorDebugLoggerArg;
}

void
initProcessParams(DataMethod dataMethod, ParserMethod parserMethod, ExporterMethod exporterMethod, Filter **filters,
                  int filters_length, Format **formats, int formats_length, ExporterColumns **columns) {
    processParams = malloc(sizeof *processParams);
    processParams->dataMethod = dataMethod;
    processParams->parserMethod = parserMethod;
    processParams->exporterMethod = exporterMethod;
    processParams->filters = filters;
    processParams->filters_length = filters_length;
    processParams->formats_conditions = formats;
    processParams->formats_conditions_length = formats_length;
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

    ParserInput *parserInput = buildParserInput(dataData);
    ParserOutput *parserData;
    ParserResult resultParser = processParams->parserMethod(&parserData, parserInput);

    if (resultParser != PARSER_RESULT_OK) {
        return PROCESS_ERROR_PARSER;
    }

    processorDebugLogger("Calling exportMethod [event:process]");
    ExporterParams *exporterParams = buildExporterParams();
    ExportResult resultExport = processParams->exporterMethod(parserData, exporterParams);

    if (resultExport != EXPORT_RESULT_OK) {
        return PROCESS_ERROR_EXPORTER;
    }

    closeResources(dataData);

    return PROCESS_OK;
}

ExporterParams *buildExporterParams() {
    ExporterParams *ep = malloc(sizeof *ep);
    ep->columns = processParams->columns;
    ep->formats_conditions = processParams->formats_conditions;
    ep->formats_conditions_length = processParams->formats_conditions_length;

    return ep;
}

ParserInput *buildParserInput(DataOutput *dataOutput) {
    ParserInput *newInput = malloc(sizeof *newInput);
    newInput->file = dataOutput->file;
    newInput->filters = processParams->filters;
    newInput->filters_length = processParams->filters_length;
    return newInput;
}


void closeResources(DataOutput *dataData) {
    fclose(dataData->file);
}
//TODO: CLOSE ALL FILES