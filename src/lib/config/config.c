#include "config.h"
#include "../logging/logging.h"

void initConfig(Logger debugLogger){
    configDebugLogger = debugLogger;
}

//getUserOS returns user's Operating System callin
char* getUserOS(){
    configDebugLogger("Getting user OS [event:getUserOS]");
    return "macOS";
}

char* getExtractorFSPath(){
    return "resources/lideres_bcba.html";
}

char* getExtractorURL(){
    return "http://tpssl.rf.gd/lideres_bcba.html";
}

char* getAuxTableFileName(){
    return "resources/aux_table_file.txt";
}

char* getExporterOutputPath(){
    return "resources/lideres_bcba_result";
}

char* getCSVDelimiter(){
    return ",";
}