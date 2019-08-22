#include "config.h"
#include "../logging/logging.h"

void initConfig(Logger debugLogger) {
    configDebugLogger = debugLogger;
}

char *getParserCMD(){
    return "";
}

char *getDataFSPath() {
    return "resources/lideres_bcba.html";
}

char *getAuxTableFileName() {
    return "output/aux_table_file.txt";
}

char *getExporterOutputPath() {
    return "output/lideres_bcba_result";
}

char *getCSVDelimiter() {
    return ",";
}