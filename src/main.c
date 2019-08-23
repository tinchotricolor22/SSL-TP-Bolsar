#include "stdio.h"
#include "libs/logging/logging.h"
#include "libs/config/config.h"
#include "libs/ui/ui.h"
#include "libs/processor/processor.h"
#include "libs/data/data.h"
#include "libs/exporter/exporter.h"
#include "libs/preferences/preferences.h"

#define DEBUG 1

//main_debug_logger is logger for debug mode in main file
static Logger main_debug_logger;

//init_main initializes global variables (like logger) to use in all the lifecycle of the program
void init_main(Logger debug_logger);

//init initializes global variables from dependencies (like logger) to use in all the lifecycle of the program
void init();

//custom_processor_injection initializes global variables from dependencies (like logger) to use in all the lifecycle of the program
//for customs reports
void custom_processor_injection(Option option_method, Option option_export);

//default_reports_processor_injection initializes global variables from dependencies (like logger) to use in all the lifecycle of the program
//for default reports
void default_reports_processor_injection(Option option_reports);

//optionsMenus calls UI and returns result code
int option_menus();

//data_method selects data get strategy for custom reports
DataMethod data_method(Option option_method);

//exporter_method returns exporter strategy for custom reports
ExporterMethod exporter_method(Option option_method);

int main() {
    init();
    main_debug_logger("Starting config [event:main]");
    ResultConfig result_config = init_config_properties();
    if (result_config == RESULT_CONFIG_ERROR) {
        return result_config;
    }

    main_debug_logger("Starting preferences options [event:main]");
    Option result = option_menus();
    if (result == EXIT) {
        return EXIT;
    }

    main_debug_logger("Processing [event:main]");
    ProcessResult processResult = process();

    if (processResult != PROCESS_OK) {
        print_final_error_message(processResult);
    }

    main_debug_logger("Process ends with result %d [event:main]", processResult);
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

    init_main(debugLogger);
    init_config(debugLogger);
    init_UI(stdLogger);
    init_data(debugLogger);
    initParser(debugLogger);
    initExporter(debugLogger);
    init_processor(debugLogger);
}

void init_main(Logger debug_logger) {
    main_debug_logger = debug_logger;
}

int option_menus() {
    Option option_reports = reports_option_menu();
    if (option_reports == EXIT) {
        return EXIT;
    }

    Option option_method, option_export;

    if (option_reports == REPORT_CUSTOM) {
        option_method = method_options_menu();
        if (option_method == EXIT) {
            return EXIT;
        }

        option_export = export_options_menu();
        if (option_export == EXIT) {
            return EXIT;
        }

        main_debug_logger("Preparing processor for custom preferences [event:main]");
        custom_processor_injection(option_method, option_export);

    } else {
        main_debug_logger("Preparing processor for default preferences [event:main]");
        default_reports_processor_injection(option_reports);
    }
}

void default_reports_processor_injection(Option option_reports) {
    ProcessParams *process_params;

    switch (option_reports) {
        case REPORT_LEADERS_05_VARIATION_SCREEN:
            process_params = default_leaders_05_variation_screen();
            break;
        case REPORT_LEADERS_05_VARIATION_HTML:
            process_params = default_leaders_05_variation_HTML();
            break;
        case REPORT_LEADERS_SALE_PURCHASE_CSV:
            process_params = default_leaders_sale_purchase_CSV();
            break;
    }

    init_process_params(process_params->data_method,
                        process_params->parser_method,
                        process_params->exporter_method,
                        process_params->filters_list,
                        process_params->filters_list_length,
                        process_params->formats_conditions_list,
                        process_params->formats_conditions_list_length,
                        &process_params->p_columns);
}

//custom_processor_injection creates a new processorParams depending of method and export methods selected
void custom_processor_injection(Option option_method, Option option_export) {
    main_debug_logger("Options selected [event:processOptions] [option_method:%d] [option_export:%d]", option_method,
                      option_export);

    ProcessParams *processParams = default_preferences();

    processParams->data_method = data_method(option_method);
    processParams->exporter_method = exporter_method(option_export);

    init_process_params(processParams->data_method,
                        processParams->parser_method,
                        processParams->exporter_method,
                        processParams->filters_list,
                        processParams->filters_list_length,
                        processParams->formats_conditions_list,
                        processParams->formats_conditions_list_length,
                        &processParams->p_columns);
}

DataMethod data_method(Option option_method) {
    switch (option_method) {
        case METHOD_ONLINE:
            return _get_data_with_online_method;
        default:
            return _get_data_with_fs_method;
    }
}

ExporterMethod exporter_method(Option option_method) {
    switch (option_method) {
        case EXPORT_CSV:
            return exportCSV;
        case EXPORT_HTML:
            return exportHTML;
        default:
            return exportStdout;
    }
}