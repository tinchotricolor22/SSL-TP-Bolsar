#include "../logging/logging.h"

#define EXIT 0

// METHODS OPTIONS
#define METHOD_ONLINE 1
#define METHOD_FS 2

// EXPORT OPTIONS
#define EXPORT_CSV 1
#define EXPORT_HTML 2
#define EXPORT_STDOUT 3

// Reports
#define REPORT_LEADERS_05_VARIATION_SCREEN 1
#define REPORT_LEADERS_05_VARIATION_HTML 2
#define REPORT_LEADERS_SALE_PURCHASE_CSV 3
#define REPORT_CUSTOM 4

//Option represents option selected by user
typedef int Option;

//ui_logger is logger for ui
Logger ui_logger;

//init_UI inits ui_logger
void init_UI(Logger);

//method_options_menu prints the menu to select an scraping method
//returns selected option
Option method_options_menu();

//export_options_menu prints the menu to select an export method
//returns selected option
Option export_options_menu();

//reports_option_menu prints the menu to select default or custom report
//returns selected option
Option reports_option_menu();

//print_final_error_message prints error message with error code
void print_final_error_message(int error_code);

