#include "processor.h"
//#include "../extractor/extractor.h"
//#include "../exporter/exporter.h"
//#include "../logging/logging.h"

Logger processorDebugLogger;

void initProcessor(Logger processorDebugLoggerArg){
    processorDebugLogger = processorDebugLoggerArg;
}

void initProcessorMethods(ExtractorMethod extractorMethodArg,ExporterMethod exporterMethodArg, ColumnsExporterOptions* columnsOptionsArg){
    extractorMethod = extractorMethodArg;
    exporterMethod = exporterMethodArg;
    columnsOptions = columnsOptionsArg;
}

ProcessResult process(){
    processorDebugLogger("Calling extractorMethod [event:process]");
    Data* data = extractorMethod();

    processorDebugLogger("Calling exporterMethod [event:process]");
    ExportResult result = exporterMethod(data,columnsOptions);

    return PROCESS_OK;
}