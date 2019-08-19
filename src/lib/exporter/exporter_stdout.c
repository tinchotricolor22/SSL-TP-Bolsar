#include "exporter.h"
#include "stdio.h"

ExportResult exportLeadersStdout(Data *data, ExporterParams *params) {
    exporterDebugLogger("Starting export in stdout [event:exportLeadersStdout]");

    writeCSVFileWithData(stdout, data, params->columns);

    exporterDebugLogger("Export in stdout succesfully [event:exportLeadersStdout]");
    return EXPORT_RESULT_OK;
}