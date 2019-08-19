#include "processortypes.h"
#include "../logging/logging.h"

ProcessParams *processParams;

void initProcessor(Logger processorDebugLoggerArg);

void initProcessParams(ParserMethod parserMethod, ExporterMethod exporterMethod, Filters *filters,
                       Formatter **formatter, ExporterColumns **columns);

ExporterParams *buildExporterParams();

ProcessResult process();
