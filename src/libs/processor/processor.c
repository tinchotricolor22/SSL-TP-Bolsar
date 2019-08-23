#include "processor.h"
#include "../exporter/exportertypes.h"
#include "stdio.h"
#include "stdlib.h"

//build_exporter_params returns exporter params from process params
static ExporterParams *build_exporter_params();

//build_parser_input returns parser input from process params and data output
static ParserInput *build_parser_input(DataOutput *);

//close_resources free pointers
static void close_resources(DataOutput *p_data_data);

void init_processor(const Logger processor_debug_logger_arg) {
    processor_debug_logger = processor_debug_logger_arg;
}

void
init_process_params(const DataMethod data_method, const ParserMethod parserMethod, const ExporterMethod exporterMethod,
                    const Filter **filters,
                    const int filters_length, const Format **formats, const int formats_length,
                    const ExporterColumns **p_columns) {
    g_p_process_params = malloc(sizeof *g_p_process_params);
    g_p_process_params->data_method = data_method;
    g_p_process_params->parser_method = parserMethod;
    g_p_process_params->exporter_method = exporterMethod;
    g_p_process_params->filters_list = filters;
    g_p_process_params->filters_list_length = filters_length;
    g_p_process_params->formats_conditions_list = formats;
    g_p_process_params->formats_conditions_list_length = formats_length;
    g_p_process_params->p_columns = *p_columns;
}

ProcessResult process() {
    processor_debug_logger("Calling data method [event:process]");

    DataOutput *p_data_data;
    DataResult result_data = g_p_process_params->data_method(&p_data_data);

    if (result_data != DATA_RESULT_OK) {
        return PROCESS_ERROR_DATA;
    }

    processor_debug_logger("Calling parser method [event:process]");

    ParserInput *p_parser_input = build_parser_input(p_data_data);
    ParserOutput *p_parser_data;
    ParserResult result_parser = g_p_process_params->parser_method(&p_parser_data, p_parser_input);

    if (result_parser != PARSER_RESULT_OK) {
        return PROCESS_ERROR_PARSER;
    }

    processor_debug_logger("Calling exporter method [event:process]");
    ExporterParams *p_exporter_params = build_exporter_params();
    ExportResult result_export = g_p_process_params->exporter_method(p_parser_data, p_exporter_params);

    if (result_export != EXPORT_RESULT_OK) {
        return PROCESS_ERROR_EXPORTER;
    }

    close_resources(p_data_data);

    return PROCESS_OK;
}

static ExporterParams *build_exporter_params() {
    ExporterParams *p_ep = malloc(sizeof *p_ep);
    p_ep->columns = g_p_process_params->p_columns;
    p_ep->formats_conditions = g_p_process_params->formats_conditions_list;
    p_ep->formats_conditions_length = g_p_process_params->formats_conditions_list_length;

    return p_ep;
}

static ParserInput *build_parser_input(DataOutput *p_data_output) {
    ParserInput *p_new_input = malloc(sizeof *p_new_input);
    p_new_input->file = p_data_output->file;
    p_new_input->filters = g_p_process_params->filters_list;
    p_new_input->filters_length = g_p_process_params->filters_list_length;
    return p_new_input;
}


static void close_resources(DataOutput *p_data_data) {
    //TODO: CLOSE ALL FILES
    fclose(p_data_data->file);
}
