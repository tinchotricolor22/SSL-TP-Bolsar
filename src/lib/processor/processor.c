#include "processor.h"
#include "../extractor/extractortypes.h"
#include "../exporter/exportertypes.h"
#include "stdlib.h"

Logger processorDebugLogger;

void initProcessor(Logger processorDebugLoggerArg){
    processorDebugLogger = processorDebugLoggerArg;
}

void initProcessParams(ExtractorMethod extractorMethod, ExporterMethod exporterMethod, Formatter** formatter, ExporterColumns** columns){
    processParams = malloc(sizeof *processParams);
    processParams->extractorMethod = extractorMethod;
    processParams->exporterMethod = exporterMethod;
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

    ExporterParams *exporterParams = buildExporterParams();
    
    ExportResult resultExport = processParams->exporterMethod(data,exporterParams);

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