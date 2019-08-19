#ifndef PROCESSOR_TYPES_HEADER
#define PROCESSOR_TYPES_HEADER

#include "../exporter/exportertypes.h"
#include "../extractor/extractortypes.h"
#include "../formatter/formattertypes.h"
#include "../filter/filter.h"

#define PROCESS_OK 0
#define PROCESS_ERROR_EXTRACTOR 1
#define PROCESS_ERROR_FILTER 2
#define PROCESS_ERROR_EXPORTER 3

typedef struct ProcessParams {
    ExtractorMethod extractorMethod;
    ExporterMethod exporterMethod;
    Filters *filters;
    Formatter *formatter; //Estos dos últimos pueden ir en un type que sea view params
    ExporterColumns *columns;
} ProcessParams;

typedef int ProcessResult;

#endif