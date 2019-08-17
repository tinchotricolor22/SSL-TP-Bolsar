#include <stdio.h>
#include <stdarg.h>
#include "lib/extractor/extractor.h"
#include "lib/exporter/exporter.h"

#define EXIT 0
#define DEBUG 1

int(*mainLogger)(const char*,...);
int(*mainDebugLogger)(const char*,...);

void initMainGlobalVariables(int(*stdLogger)(const char*,...),int(*debugLogger)(const char*,...));
void injectGlobalVariables();
char* getUserOS();
char* getFSPath();
char* getURL();
int printLn(const char* message, ...);
int printfDebug(const char* message, ...);
int printfNone(const char* message, ...);
Option methodOptionsMenu();
Option exportOptionsMenu();
void printExportResult(ExportResult result);

int main(){
    injectGlobalVariables();
    Option a = 2;
    mainDebugLogger("Starting program after dependency injection [event:main]");

    Option optionMethod = methodOptionsMenu();
    if (optionMethod == EXIT) {
        return 0;
    }
    
    Option optionExport = exportOptionsMenu();
    if (optionExport == EXIT) {
        return 0;
    }
    
    mainDebugLogger("Calling extractData [event:main] [option_method:%d]",optionMethod);
    Data data = extractData(optionMethod);

    mainDebugLogger("Calling exportData [event:main] [option_export:%d]",optionExport);
    ExportResult result = exportData(optionExport, data);
    
    printExportResult(result);
}

//injectGlobalVariables intializes global variables to use in all the lifecycle of the program
void injectGlobalVariables(){
    int(*stdLogger)(const char*,...) = printLn;
    int(*debugLogger)(const char*,...);
    if(DEBUG){
        debugLogger = printfDebug;
    }else{
        debugLogger = printfNone;
    }
    initMainGlobalVariables(stdLogger,debugLogger);

    char* userOS = getUserOS();
    char* URL = getURL();
    char* FSPath = getFSPath();
    
    initExtractorGlobalVariables(userOS,URL,FSPath,stdLogger,debugLogger);
}

void initMainGlobalVariables(int(*stdLogger)(const char*,...),int(*debugLogger)(const char*,...)){
    mainLogger = stdLogger;
    mainDebugLogger = debugLogger;
}

//getUserOS returns user's Operating System 
char* getUserOS(){
    mainDebugLogger("Getting user OS [event:getUserOS]");
    return "macOS";
}

char* getFSPath(){
    return "resources/lideres_bcba.html";
}

char* getURL(){
    return "http://tpssl.rf.gd/lideres_bcba.html";
}


//methodOptions prints the menu to select an scrapping method
//returns selected option
Option methodOptionsMenu(){
    Option methodOption;
    mainLogger("Scrapping type\n");
    mainLogger("%d- Bolsar info online\n",METHOD_ONLINE);
    mainLogger("%d- Bolsar info from fileSystem\n",METHOD_FS);
    mainLogger("%d- Exit\n",EXIT);
    mainLogger("Select an option: ");
    scanf("%d", &methodOption);

    //Default
    if (methodOption != EXIT && methodOption != METHOD_ONLINE && methodOption != METHOD_FS){
        methodOption = EXIT;
    }

    return methodOption;
}

//methodOptions prints the menu to select export options
//returns selected option
Option exportOptionsMenu(){
    Option exportOption;
    mainLogger("Export types\n");
    mainLogger("%d- CSV\n",EXPORT_CSV);
    mainLogger("%d- XLSX\n",EXPORT_XLSX);
    mainLogger("%d- Exit\n",EXIT);
    mainLogger("Select an option: ");
    scanf("%d", &exportOption);

    //Default
    if (exportOption != EXIT && exportOption != EXPORT_CSV && exportOption != EXPORT_XLSX){
        exportOption = EXIT;
    }

    return exportOption;
}

//printExportResult prints view for exportResult
void printExportResult(ExportResult result){
    mainLogger("%d",result);
};

//printLn calls printf and adds \n at the end of the line
int printLn(const char* message, ...){
    va_list args;
    va_start(args,message);
    vprintf(message,args); // TODO: Return printf int
    va_end(args);
    return printf("\n");
}

//printfDebug calls printf, puts [DEBUG] string before the message and \n at end of the line
int printfDebug(const char* message, ...){
    va_list args;
    va_start(args,message);
    printf("[DEBUG] ");
    vprintf(message,args); // TODO: Return printf int
    va_end(args);
    return printf("\n");
}

//printfNone returns 0. Must be used to avoid output messages.
int printfNone(const char* message, ...){
    return 0;
}