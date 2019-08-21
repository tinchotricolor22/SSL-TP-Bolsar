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
#include "lib/preferences/preferences.h"

#define DEBUG 1

Logger mainDebugLogger;

void initMain(Logger debugLogger);

void init();

void customProcessorInjection(Option optionMethod, Option optionExport);

void defaultReportsProcessorInjection(Option optionReport);

int optionMenus();

DataMethod dataMethod(Option optionMethod);

ParserMethod parser();

ExporterMethod exporterMethod(Option optionMethod);

ExporterColumns *columns();

Formatter *formatter();

Filters *filters();

int main() {
    init();

    mainDebugLogger("Starting preferences options [event:main]");
    Option result = optionMenus();
    if (result == EXIT) {
        return 0;
    }

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

int optionMenus() {
    Option optionReports = reportsOptionMenu();
    if (optionReports == EXIT) {
        return 0;
    }

    Option optionMethod, optionExport;

    if (optionReports == REPORT_CUSTOM) {
        optionMethod = methodOptionsMenu();
        if (optionMethod == EXIT) {
            return 0;
        }

        optionExport = exportOptionsMenu();
        if (optionExport == EXIT) {
            return 0;
        }

        mainDebugLogger("Preparing processor for custom preferences [event:main]");
        customProcessorInjection(optionMethod, optionExport);

    } else {
        mainDebugLogger("Preparing processor for default preferences [event:main]");
        defaultReportsProcessorInjection(optionReports);
    }
}

void defaultReportsProcessorInjection(Option optionReports) {
    ProcessParams *processParams;

    switch (optionReports) {
        case REPORT_LEADERS_05_VARIATION_SCREEN:
            processParams = defaultLeaders05VariationScreen();
            break;
        case REPORT_LEADERS_05_VARIATION_HTML:
            processParams = defaultLeaders05VariationHTML();
            break;
        case REPORT_LEADERS_SALE_PURCHASE_CSV:
            processParams = defaultLeadersSalePurchaseCSV();
            break;
    }

    initProcessParams(processParams->dataMethod,
                      processParams->parserMethod,
                      processParams->exporterMethod,
                      processParams->filters == NULL ? NULL : processParams->filters,
                      &processParams->formatter == NULL ? NULL : &processParams->formatter,
                      &processParams->columns);
}

//customProcessorInjection instance parser and exporter option
void customProcessorInjection(Option optionMethod, Option optionExport) {
    mainDebugLogger("Options selected [event:processOptions] [option_method:%d] [option_export:%d]", optionMethod,
                    optionExport);

    ProcessParams *processParams = defaultPreferences();

    processParams->dataMethod = dataMethod(optionMethod);
    processParams->exporterMethod = exporterMethod(optionExport);

    initProcessParams(processParams->dataMethod,
                      processParams->parserMethod,
                      processParams->exporterMethod,
                      processParams->filters == NULL ? NULL : processParams->filters,
                      &processParams->formatter == NULL ? NULL : &processParams->formatter,
                      &processParams->columns);
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
            return exportCSV;
            break;

        case EXPORT_HTML:
            return exportHTML;
            break;

        default:
            return exportStdout;
            break;
    }
}