#include "config.h"
#include "../logging/logging.h"

void initConfig(Logger debugLogger) {
    configDebugLogger = debugLogger;
}

char *getDataFSPath() {
    return "src/resources/lideres_bcba.html";
}

char *getAuxTableFileName() {
    return "src/output/aux_table_file.txt";
}

char *getExporterOutputPath() {
    return "src/output/lideres_bcba_result";
}

char *getCSVDelimiter() {
    return ",";
}