#include "stdio.h"
#include "unistd.h"
#include "lib/logging/logging.h"
#include "lib/config/config.h"
#include "lib/ui/ui.h"
#include "lib/processor/processor.h"    
#include "lib/extractor/extractor.h"
#include "lib/filter/filter.h"
#include "lib/formatter/formatter.h"
#include "lib/exporter/exporter.h"

#define DEBUG 1

Logger mainLogger;
Logger mainDebugLogger;

void initMain(Logger stdLogger,Logger debugLogger);
void init();
void processorMethods(Option optionMethod,Option optionExport);

ExtractorMethod extractorMethod(Option optionMethod);
ExporterMethod exporterMethod(Option optionMethod);
ExporterColumns* columns();
Formatter* formatter();
Filters* filters();

int main(){
    init();
    
    mainDebugLogger("Starting method options [event:main]");
    Option optionMethod = methodOptionsMenu();
    if (optionMethod == EXIT) {
        return 0;
    }
    
    Option optionExport = exportOptionsMenu();
    if (optionExport == EXIT) {
        return 0;
    }

    mainDebugLogger("Preparing processor [event:main]");
    processorMethods(optionMethod,optionExport);

    mainDebugLogger("Processing [event:main]");
    ProcessResult processResult = process();
    
    if(processResult != PROCESS_OK){
        printFinalErrorMessage(processResult);
    }
    
    mainDebugLogger("Process ends with result %d [event:main]", processResult);
    return processResult;
}

//init intializes global variables like logger to use in all the lifecycle of the program
void init(){
    Logger stdLogger = printf;
    Logger debugLogger;
    if(DEBUG){
        debugLogger = printfDebug;
    }else{
        debugLogger = printfNone;
    }

    initMain(stdLogger,debugLogger);
    initUI(stdLogger);
    initConfig(debugLogger);
    initExtractor(stdLogger,debugLogger);
    initExporter(debugLogger);
    initProcessor(debugLogger);
}

//init sets logger variables
void initMain(Logger stdLogger,Logger debugLogger){
    mainLogger = stdLogger;
    mainDebugLogger = debugLogger;
}

//processorMethods instance extractor and exporter option
void processorMethods(Option optionMethod,Option optionExport){
    mainDebugLogger("Options selected [event:processOptions] [option_method:%d] [option_export:%d]",optionMethod,optionExport);

    ExtractorMethod extractor = extractorMethod(optionMethod);
    ExporterMethod exporter = exporterMethod(optionExport);
    Filters* filts = filters();
    ExporterColumns* cols = columns();
    Formatter* formatt = formatter();
    

    initProcessParams(extractor,exporter,filts,&formatt,&cols);
}

//extractorOption selects extractor strategy
ExtractorMethod extractorMethod(Option optionMethod){
    switch (optionMethod)
    {
        case METHOD_ONLINE:
            return extractDataWithOnlineMethod;
        break;

        default:
            return extractDataWithFSMethod;
        break;
    }
}

//exportMetod selects exporter strategy
ExporterMethod exporterMethod(Option optionMethod){
    switch (optionMethod)
    {
        case EXPORT_CSV:
            return exportLeadersCSV;
        break;

        case EXPORT_HTML:
            return exportHTML;
        break;

        default:
            return exportLeadersStdout;
        break;
    }
}

ExporterColumns* columns(){
    return buildLeaderColumns(1,1,1,1,1,1,1);
}

Formatter* formatter(){
    return buildLeaderFormatter();
}

Filters* filters(){
    return buildLeaderFilters();
}  

/*ExporterMethod filterOptions(Option optionMethod){
}*/