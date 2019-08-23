#include "stdio.h"
#include "libs/logging/logging.h"
#include "libs/config/config.h"
#include "libs/ui/ui.h"
#include "libs/processor/processor.h"
#include "libs/data/data.h"
#include "libs/parser/parser.h"
#include "libs/formatter/formatter.h"
#include "libs/exporter/exporter.h"
#include "libs/preferences/preferences.h"

#define DEBUG 1

//mainDebugLogger is logger for debug mode in main file
static Logger mainDebugLogger;

//initMain initializes global variables (like logger) to use in all the lifecycle of the program
void initMain(Logger);

//init initializes global variables from dependencies (like logger) to use in all the lifecycle of the program
void init();

//customProcessorInjection initializes global variables from dependencies (like logger) to use in all the lifecycle of the program
//for customs reports
void customProcessorInjection(Option optionMethod, Option optionExport);

//defaultReportsProcessorInjection initializes global variables from dependencies (like logger) to use in all the lifecycle of the program
//for default reports
void defaultReportsProcessorInjection(Option optionReport);

//optionsMenus calls UI and returns result code
int optionMenus();

//data_method selects data get strategy for custom reports
DataMethod dataMethod(Option optionMethod);

//exporter_method returns exporter strategy for custom reports
ExporterMethod exporterMethod(Option optionMethod);

int main() {
    init();
    mainDebugLogger("Starting config [event:main]");
    ResultConfig result_config = init_config();
    if (result_config == RESULT_CONFIG_ERROR){
        return result_config;
    }

    mainDebugLogger("Starting preferences options [event:main]");
    Option result = optionMenus();
    if (result == EXIT) {
        return EXIT;
    }

    mainDebugLogger("Processing [event:main]");
    ProcessResult processResult = process();

    if (processResult != PROCESS_OK) {
        printFinalErrorMessage(processResult);
    }

    mainDebugLogger("Process ends with result %d [event:main]", processResult);
    return processResult;
}

void init() {
    Logger stdLogger = printf;
    Logger debugLogger;
    if (DEBUG) {
        debugLogger = printf_debug;
    } else {
        debugLogger = printf_none;
    }

    initMain(debugLogger);
    initUI(stdLogger);
    init_data(debugLogger);
    initParser(debugLogger);
    initExporter(debugLogger);
    init_processor(debugLogger);
}

void initMain(Logger debugLogger) {
    mainDebugLogger = debugLogger;
}

int optionMenus() {
    Option optionReports = reportsOptionMenu();
    if (optionReports == EXIT) {
        return EXIT;
    }

    Option optionMethod, optionExport;

    if (optionReports == REPORT_CUSTOM) {
        optionMethod = methodOptionsMenu();
        if (optionMethod == EXIT) {
            return EXIT;
        }

        optionExport = exportOptionsMenu();
        if (optionExport == EXIT) {
            return EXIT;
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
            processParams = default_leaders_05_variation_screen();
            break;
        case REPORT_LEADERS_05_VARIATION_HTML:
            processParams = default_leaders_05_variation_HTML();
            break;
        case REPORT_LEADERS_SALE_PURCHASE_CSV:
            processParams = default_leaders_sale_purchase_CSV();
            break;
    }

    init_process_params(processParams->data_method,
                        processParams->parser_method,
                        processParams->exporter_method,
                        processParams->filters_list,
                        processParams->filters_list_length,
                        processParams->formats_conditions_list,
                        processParams->formats_conditions_list_length,
                        &processParams->p_columns);
}

//customProcessorInjection creates a new processorParams depending of method and export methods selected
void customProcessorInjection(Option optionMethod, Option optionExport) {
    mainDebugLogger("Options selected [event:processOptions] [option_method:%d] [option_export:%d]", optionMethod,
                    optionExport);

    ProcessParams *processParams = default_preferences();

    processParams->data_method = dataMethod(optionMethod);
    processParams->exporter_method = exporterMethod(optionExport);

    init_process_params(processParams->data_method,
                        processParams->parser_method,
                        processParams->exporter_method,
                        processParams->filters_list,
                        processParams->filters_list_length,
                        processParams->formats_conditions_list,
                        processParams->formats_conditions_list_length,
                        &processParams->p_columns);
}

DataMethod dataMethod(Option optionMethod) {
    switch (optionMethod) {
        case METHOD_ONLINE:
            return _get_data_with_online_method;
        default:
            return _get_data_with_fs_method;
    }
}

ExporterMethod exporterMethod(Option optionMethod) {
    switch (optionMethod) {
        case EXPORT_CSV:
            return exportCSV;
        case EXPORT_HTML:
            return exportHTML;
        default:
            return exportStdout;
    }
}