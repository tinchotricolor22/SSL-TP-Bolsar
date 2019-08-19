#include "processor.h"
#include "../extractor/extractortypes.h"
#include "../exporter/exportertypes.h"
#include "../filter/filter.h"
#include "stdlib.h"

Logger processorDebugLogger;

void initProcessor(Logger processorDebugLoggerArg){
    processorDebugLogger = processorDebugLoggerArg;
}

void initProcessParams(ExtractorMethod extractorMethod, ExporterMethod exporterMethod,Filters* filters, Formatter** formatter, ExporterColumns** columns){
    processParams = malloc(sizeof *processParams);
    processParams->extractorMethod = extractorMethod;
    processParams->exporterMethod = exporterMethod;
    processParams->filters = filters;
    processParams->formatter = *formatter;
    processParams->columns = *columns;
}

ProcessResult process(){
    processorDebugLogger("Calling extractorMethod [event:process]");
    Data *data;
    ExtractorResult resultExtractor = processParams->extractorMethod(&data);

    if(resultExtractor != EXTRACTOR_RESULT_OK){
        return PROCESS_ERROR_EXTRACTOR;
    }
    
    processorDebugLogger("Calling filters [event:process]");
    Data *filteredData = malloc(sizeof *filteredData);
    executeFilters(data,&filteredData);

    processorDebugLogger("Calling exportMethod [event:process]");
    ExporterParams *exporterParams = buildExporterParams();
    ExportResult resultExport = processParams->exporterMethod(&filteredData,exporterParams);

    if(resultExport != EXPORT_RESULT_OK){
        return PROCESS_ERROR_EXPORTER;
    }

    return PROCESS_OK;
}

ExporterParams* buildExporterParams(){
    ExporterParams *ep = malloc(sizeof *ep);
    ep->columns = processParams->columns;
    ep->formatter = processParams->formatter;

    return ep;
}

FilterResult executeFilters(Data* data, Data* filteredData){
    for(int i = 0 ; i< processParams->filters->filter_list_length ; i++){

       Filter execFilter = processParams->filters->filter_list[i];
       execFilter(data,filteredData);
    }
    return FILTER_RESULT_OK;
}