//#include "../extractor/extractor.h" TODO: Cuando arregle el tema de Data de input y output se va a poder volver a poner esto
#include "../exporter/exporter.h"
#include "../logging/logging.h"

#define PROCESS_OK 0
#define PROCESS_ERROR_EXTRACTOR 1
#define PROCESS_ERROR_EXPORTER 2

ExtractorMethod extractorMethod;
ExporterMethod exporterMethod;
ColumnsExporterOptions* columnsOptions;

typedef int ProcessResult;

void initProcessor(Logger processorDebugLoggerArg);
void initProcessorMethods(ExtractorMethod extractorMethodArg,ExporterMethod exporterMethodArg, ColumnsExporterOptions* columnsOptionsArg);
ProcessResult process();