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

typedef int Option;

void initUI(Logger stdLogger);

Option methodOptionsMenu();

Option exportOptionsMenu();

Option reportsOptionMenu();

void printFinalErrorMessage(int errorCode);

Logger uiLogger;