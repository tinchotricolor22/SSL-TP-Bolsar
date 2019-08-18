#include "processor.h"
//#include "../extractor/extractor.h"
//#include "../exporter/exporter.h"
//#include "../logging/logging.h"

Logger processorDebugLogger;

void initProcessor(Logger processorDebugLoggerArg){
    processorDebugLogger = processorDebugLoggerArg;
}

void initProcessorMethods(ExtractorMethod extractorMethodArg,ExporterMethod exporterMethodArg){
    extractorMethod = extractorMethodArg;
    exporterMethod = exporterMethodArg;
}

ProcessResult process(){
    processorDebugLogger("Calling extractorMethod [event:process]");
    Data* data = extractorMethod();

    processorDebugLogger("Calling exportData [event:process]");
    ExportResult result = exporterMethod(data);

    return PROCESS_OK;
}