#include "processortypes.h"
#include "../logging/logging.h"

ProcessParams *processParams;

void initProcessor(Logger processorDebugLoggerArg);

void initProcessParams(DataMethod dataMethod, ParserMethod parserMethod, ExporterMethod exporterMethod, Filters *filters,
                       Formatter **formatter, ExporterColumns **columns);

FilterResult executeFilters(ParserOutput *data, FilterOutput **filteredData);

ExporterParams *buildExporterParams();

ProcessResult process();

void closeResources(DataOutput *dataData);
