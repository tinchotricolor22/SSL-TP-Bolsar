#include "exporter.h"
#include "../config/config.h"
#include "../logging/logging.h"
#include "string.h"
#include "stdio.h"

ExportResult exportLeadersStdout(Data* data, ColumnsExporterOptions *columns){
    exporterDebugLogger("Starting export in stdout [event:exportLeadersStdout]");    

    writeCSVFileWithData(stdout, data, columns);

    exporterDebugLogger("Export in stdout succesfully [event:exportLeadersStdout]");
    return EXPORT_OK;
}