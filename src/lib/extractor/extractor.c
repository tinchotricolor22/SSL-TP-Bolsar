#include <stdio.h>
#include "extractor.h"

// Can be string or another table.
typedef struct TD{
    void *type;

} TD;
typedef struct TR{
    struct TD cols[100];
} TR;

typedef struct TBody{
    struct TR rows[100];
} TBody;

typedef struct Table{
    struct TBody tbody;
} Table;


void initExtractorGlobalVariables(char* userOS, char* url, char* fsPath, int(*stdLogger)(const char*,...),int(*debugLogger)(const char*,...)){
    UserOS = userOS;
    FSPath = fsPath;
    URL = url;
    extractorLogger = stdLogger;
    extractorDebugLogger = debugLogger;
}

Data extractData(Option optionMethod){
    switch (optionMethod)
    {
        case METHOD_ONLINE:
            return extractDataWithOnlineMethod();
        break;

        default:
            return extractDataWithFSMethod();
        break;
    }
}

Data extractDataWithOnlineMethod(){
    extractorDebugLogger("Starting to extract data with online method [event:extractDataWithOnlineMethod]");
    return "asd";
}

Data extractDataWithFSMethod(){
    extractorDebugLogger("Starting to extract data with filesystem method [event:extractDataWithFSMethod]");
    FILE *file;

    file = fopen(FSPath,"r");

    if (file == NULL){
        extractorLogger("ERROR: Cannot open file in path: %s [event:extractDataWithFSMethod]",FSPath);
    }

    Data data = extractHTMLFromTableID("tbPanelALideres",&file);

    fclose(file);
    return data;
}


Data extractHTMLFromTableID(char* tableID, FILE* htmlFile){
    do{
        char* line;
        fgets(line,200,htmlFile);
        if(strstr(line,tableID)){
            break;
        }
    }while(!feof);

    fscanf("")

    TD td = { };
    TR tr[] = {td};
    TBody tbody = {tr};
    Table mainTable = {tbody};
}