#include "stdio.h"
#include "lib/logging/logging.h"
#include "lib/config/config.h"
#include "lib/ui/ui.h"
#include "lib/processor/processor.h"
#include "lib/data/data.h"
#include "lib/parser/parser.h"
#include "lib/filter/filter.h"
#include "lib/formatter/formatter.h"
#include "lib/exporter/exporter.h"

#define DEBUG 1

Logger mainDebugLogger;

void initMain(Logger debugLogger);

void init();

void processorMethods(Option optionMethod, Option optionExport);

DataMethod dataMethod(Option optionMethod);

ParserMethod parser();

ExporterMethod exporterMethod(Option optionMethod);

ExporterColumns *columns();

Formatter *formatter();

Filters *filters();

int main() {
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
    processorMethods(optionMethod, optionExport);

    mainDebugLogger("Processing [event:main]");
    ProcessResult processResult = process();

    if (processResult != PROCESS_OK) {
        printFinalErrorMessage(processResult);
    }

    mainDebugLogger("Process ends with result %d [event:main]", processResult);
    return processResult;
}

//init intializes global variables like logger to use in all the lifecycle of the program
void init() {
    Logger stdLogger = printf;
    Logger debugLogger;
    if (DEBUG) {
        debugLogger = printfDebug;
    } else {
        debugLogger = printfNone;
    }

    initMain(debugLogger);
    initUI(stdLogger);
    initConfig(debugLogger);
    initData(debugLogger);
    initParser(debugLogger);
    initExporter(debugLogger);
    initProcessor(debugLogger);
}

//init sets logger variables
void initMain(Logger debugLogger) {
    mainDebugLogger = debugLogger;
}

//processorMethods instance parser and exporter option
void processorMethods(Option optionMethod, Option optionExport) {
    mainDebugLogger("Options selected [event:processOptions] [option_method:%d] [option_export:%d]", optionMethod,
                    optionExport);

    DataMethod dataParam = dataMethod(optionMethod);
    ParserMethod parserParam = parser();
    ExporterMethod exporterParam = exporterMethod(optionExport);
    Filters *filtersParam = filters();
    ExporterColumns *columsParam = columns();
    Formatter *formatterParam = formatter();


    initProcessParams(dataParam, parserParam, exporterParam, filtersParam, &formatterParam, &columsParam);
}

//dataMethod selects data get strategy
DataMethod dataMethod(Option optionMethod) {
    switch (optionMethod) {
        case METHOD_ONLINE:
            return getDataWithOnlineMethod;
            break;

        default:
            return getDataWithFSMethod;
            break;
    }
}

//exportMetod selects exporter strategy
ExporterMethod exporterMethod(Option optionMethod) {
    switch (optionMethod) {
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

//parserMethod selects parser strategy
ParserMethod parser() {
    return parseDataFromHTML;
}

ExporterColumns *columns() {
    return buildLeaderColumns(1, 1, 1, 1, 1, 1, 1);
}

Formatter *formatter() {
    return buildLeaderFormatter();
}

Filters *filters() {
    return buildLeaderFilters();
}


/*ExporterMethod filterOptions(Option optionMethod){
}*/