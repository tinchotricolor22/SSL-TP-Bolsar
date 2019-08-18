#include "../extractor/extractor.h"
#include "../exporter/exporter.h"
#include "../logging/logging.h"


#define PROCESS_OK 0
#define PROCESS_ERROR_EXTRACTOR 1
#define PROCESS_ERROR_EXPORTER 2

ExtractorMethod extractorMethod;
ExporterMethod exporterMethod;

typedef int ProcessResult;

void initProcessor(Logger processorDebugLoggerArg);
void initProcessorMethods(ExtractorMethod extractorMethodArg,ExporterMethod exporterMethodArg);
ProcessResult process();