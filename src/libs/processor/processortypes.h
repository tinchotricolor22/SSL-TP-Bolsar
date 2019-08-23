#ifndef PROCESSOR_TYPES_HEADER
#define PROCESSOR_TYPES_HEADER

#include "../exporter/exportertypes.h"
#include "../parser/parser.h"
#include "../formatter/formatter.h"
#include "../data/data.h"
#include "../filter/filter.h"

#define PROCESS_OK 0
#define PROCESS_ERROR_DATA 1
#define PROCESS_ERROR_PARSER 2
#define PROCESS_ERROR_EXPORTER 3

typedef struct ProcessParams {
    DataMethod dataMethod;
    ParserMethod parserMethod;
    ExporterMethod exporterMethod;
    ExporterColumns *columns;
    FormatCondition **formats_conditions; //TODO:Estos tres columns,formats_conditions y formats_legnth últimos pueden ir en un type que sea view params
    int formats_conditions_length;
    Filter **filters;
    int filters_length;
} ProcessParams;

typedef int ProcessResult;

#endif