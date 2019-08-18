#include "../logging/logging.h"

#define EXIT 0

// METHODS OPTIONS
#define METHOD_ONLINE 1
#define METHOD_FS 2

// EXPORT OPTIONS
#define EXPORT_CSV 1
#define EXPORT_XLSX 2

typedef int Option;

void initUI(Logger stdLogger);

Option methodOptionsMenu();
Option exportOptionsMenu();

Logger uiLogger;