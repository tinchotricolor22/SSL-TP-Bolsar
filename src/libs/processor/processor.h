#include "processortypes.h"
#include "../logging/logging.h"

ProcessParams *processParams;

void initProcessor(Logger processorDebugLoggerArg);

void
initProcessParams(DataMethod dataMethod, ParserMethod parserMethod, ExporterMethod exporterMethod, Filter **filters,
                  int filters_length, Format **formats, int formats_length, ExporterColumns **columns);

ExporterParams *buildExporterParams();

ProcessResult process();

void closeResources(DataOutput *dataData);
