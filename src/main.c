#include "stdio.h"
#include "unistd.h"
//#include "lib/extractor/extractor.h"
//#include "lib/exporter/exporter.h"
#include "lib/logging/logging.h"
#include "lib/config/config.h"
#include "lib/ui/ui.h"
#include "lib/processor/processor.h"    

#define DEBUG 1

Logger mainLogger;
Logger mainDebugLogger;

void initMain(Logger stdLogger,Logger debugLogger);
void init();
void processorMethods(Option optionMethod,Option optionExport);

ExtractorMethod extractorOption(Option optionMethod);
ExporterMethod exporterOption(Option optionMethod);

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
    ProcessResult result = process();

    mainDebugLogger("Process ends with result %d [event:main]", result);
    return result;
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

    ExtractorMethod extractor = extractorOption(optionMethod);
    ExporterMethod exporter = exporterOption(optionExport);

    initProcessorMethods(extractor,exporter);
}

//extractorOption selects extractor strategy
ExtractorMethod extractorOption(Option optionMethod){
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

//exporterOption selects exporter strategy
ExporterMethod exporterOption(Option optionMethod){
    switch (optionMethod)
    {
        case EXPORT_CSV:
            return exportCSV;
        break;

        default:
            return exportHTML;
        break;
    }
}