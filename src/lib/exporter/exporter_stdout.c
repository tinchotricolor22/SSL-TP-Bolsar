#include "exporter.h"
#include "stdio.h"

ExportResult exportStdout(ParserOutput *data, ExporterParams *params) {
    exporterDebugLogger("Starting export in stdout [event:exportStdout]");

    writeCSVFileWithData(stdout, data, params->columns);

    exporterDebugLogger("Export in stdout succesfully [event:exportStdout]");
    return EXPORT_RESULT_OK;
}