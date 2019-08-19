#include "../logging/logging.h"

#define EXIT 0

// METHODS OPTIONS
#define METHOD_ONLINE 1
#define METHOD_FS 2

// EXPORT OPTIONS
#define EXPORT_CSV 1
#define EXPORT_HTML 2
#define EXPORT_STDOUT 3

typedef int Option;

void initUI(Logger stdLogger);

Option methodOptionsMenu();

Option exportOptionsMenu();

void printFinalErrorMessage(int errorCode);

Logger uiLogger;