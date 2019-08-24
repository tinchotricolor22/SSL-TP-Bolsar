#ifndef PROCESSOR_HEADER
#define PROCESSOR_HEADER

#include "../logging/logging.h"
#include "../exporter/exporter.h"
#include "parser.h"
#include "../formatter/formatter.h"
#include "../data/data.h"
#include "../filter/filter.h"

#define PROCESS_OK 0
#define PROCESS_ERROR_DATA 1
#define PROCESS_ERROR_PARSER 2
#define PROCESS_ERROR_EXPORTER 3

//ProcessParams represents structs with parameters that needs the processor
typedef struct ProcessParams {
    DataMethod data_method;
    ParserMethod parser_method;
    ExporterMethod exporter_method;
    ExporterColumns *p_columns;
    FormatCondition **formats_conditions_list; //TODO:Estos tres p_columns,formats_conditions_list y formats_legnth últimos pueden ir en un type que sea view params
    int formats_conditions_list_length;
    Filter **filters_list;
    int filters_list_length;
} ProcessParams;

//ProcessResult represents the result of processor
typedef int ProcessResult;

//g_p_process_params represents the params for processor to be used in the lifecycle
ProcessParams *g_p_process_params;

//data_debug_logger is logger for processor
Logger processor_debug_logger;

//init_processor inits processor_debug_logger
void init_processor(const Logger);

//init_process_params inits ProcessParams to execute process
void init_process_params(const DataMethod, const ParserMethod, const ExporterMethod, const Filter **, const int,
                         const Format **, const int, const ExporterColumns **);

//process executes the main flow of the program using process params and returns process result
ProcessResult process();

#endif