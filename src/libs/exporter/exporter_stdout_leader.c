#include "exporter.h"
#include "stdio.h"

ExportResult export_stdout(const ParserOutput *p_data, const ExporterParams *p_params) {
    exporter_debug_logger("Starting export in stdout [event:export_stdout]");

    write_csv_file_with_data(stdout, p_data, p_params->p_columns);

    exporter_debug_logger("Export in stdout succesfully [event:export_stdout]");
    return EXPORT_RESULT_OK;
}