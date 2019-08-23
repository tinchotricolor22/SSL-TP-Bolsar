#include "stdio.h"
#include "ui.h"
#include "../logging/logging.h"

void init_UI(const Logger std_logger) {
    ui_logger = std_logger;
}

Option method_options_menu() {
    Option method_option;
    ui_logger("Scraping method\n");
    ui_logger("%d- Bolsar info online\n", METHOD_ONLINE);
    ui_logger("%d- Bolsar info from fileSystem\n", METHOD_FS);
    ui_logger("%d- Exit\n", EXIT);
    ui_logger("Select an option: ");
    scanf("%d", &method_option);

    //Default
    if (method_option != EXIT && method_option != METHOD_ONLINE && method_option != METHOD_FS) {
        method_option = EXIT;
    }

    return method_option;
}

Option export_options_menu() {
    Option export_option;
    ui_logger("Export types\n");
    ui_logger("%d- CSV\n", EXPORT_CSV);
    ui_logger("%d- HTML\n", EXPORT_HTML);
    ui_logger("%d- Print in screen\n", EXPORT_STDOUT);
    ui_logger("%d- Exit\n", EXIT);
    ui_logger("Select an option: ");
    scanf("%d", &export_option);

    //Default
    if (export_option != EXIT && export_option != EXPORT_CSV && export_option != EXPORT_HTML &&
        export_option != EXPORT_STDOUT) {
        export_option = EXIT;
    }

    return export_option;
}

Option reports_option_menu() {
    Option report_option;
    ui_logger("Reports\n");
    ui_logger("%d- Leaders >0.5 variation (In screen)\n", REPORT_LEADERS_05_VARIATION_SCREEN);
    ui_logger("%d- Leaders >0.5 variation (HTML)\n", REPORT_LEADERS_05_VARIATION_HTML);
    ui_logger("%d- Leaders sale/purchase (CSV) \n", REPORT_LEADERS_SALE_PURCHASE_CSV);
    ui_logger("%d- Custom\n", REPORT_CUSTOM);
    ui_logger("%d- Exit\n", EXIT);
    ui_logger("Select an option: ");
    scanf("%d", &report_option);

    //Default
    if (report_option != EXIT && report_option != REPORT_LEADERS_05_VARIATION_SCREEN &&
        report_option != REPORT_LEADERS_05_VARIATION_HTML &&
        report_option != REPORT_LEADERS_SALE_PURCHASE_CSV && report_option != REPORT_CUSTOM) {
        report_option = EXIT;
    }

    return report_option;
}

void print_final_error_message(const int error_code) {
    ui_logger("The process finalize with error code: %d\n", error_code);
}