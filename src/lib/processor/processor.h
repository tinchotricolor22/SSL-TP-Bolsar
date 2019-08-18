//#include "../extractor/extractor.h" TODO: Cuando arregle el tema de Data de input y output se va a poder volver a poner esto
#include "processortypes.h"
#include "../logging/logging.h"

ProcessParams *processParams;

void initProcessor(Logger processorDebugLoggerArg);
void initProcessParams(ExtractorMethod extractorMethod, ExporterMethod exporterMethod, Formatter** formatter, ExporterColumns** columns);
ExporterParams* buildExporterParams();

ProcessResult process();
