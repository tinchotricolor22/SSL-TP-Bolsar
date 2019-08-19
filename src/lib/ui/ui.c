#include "stdio.h"
#include "ui.h"
#include "../logging/logging.h"

void initUI(Logger stdLogger) {
    uiLogger = stdLogger;
}

//methodOptions prints the menu to select an scrapping method
//returns selected option
Option methodOptionsMenu() {
    Option methodOption;
    uiLogger("Scrapping method\n");
    uiLogger("%d- Bolsar info online\n", METHOD_ONLINE);
    uiLogger("%d- Bolsar info from fileSystem\n", METHOD_FS);
    uiLogger("%d- Exit\n", EXIT);
    uiLogger("Select an option: ");
    scanf("%d", &methodOption);

    //Default
    if (methodOption != EXIT && methodOption != METHOD_ONLINE && methodOption != METHOD_FS) {
        methodOption = EXIT;
    }

    return methodOption;
}

//methodOptions prints the menu to select export options
//returns selected option
Option exportOptionsMenu() {
    Option exportOption;
    uiLogger("Export types\n");
    uiLogger("%d- CSV\n", EXPORT_CSV);
    uiLogger("%d- HTML\n", EXPORT_HTML);
    uiLogger("%d- Print in screen\n", EXPORT_STDOUT);
    uiLogger("%d- Exit\n", EXIT);
    uiLogger("Select an option: ");
    scanf("%d", &exportOption);

    //Default
    if (exportOption != EXIT && exportOption != EXPORT_CSV && exportOption != EXPORT_HTML &&
        exportOption != EXPORT_STDOUT) {
        exportOption = EXIT;
    }

    return exportOption;
}

void printFinalErrorMessage(int errorCode) {
    uiLogger("The process finalize with error code: %d\n", errorCode);
}