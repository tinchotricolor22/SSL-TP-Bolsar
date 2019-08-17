// METHODS OPTIONS
#define METHOD_ONLINE 1
#define METHOD_FS 2

typedef char* Data;
typedef int Option;

char* UserOS;
char* URL;
char* FSPath;
int(*extractorLogger)(const char*,...);
int(*extractorDebugLogger)(const char*,...);

//initExtractorGlobalVariables injects dependency variables for extractor that includes logger functions
void initExtractorGlobalVariables(char* userOS, char* url, char* fsPath, int(*stdLogger)(const char*,...),int(*debugLogger)(const char*,...));

//extractData is a wrapper for select the method for extract depending the option selected
Data extractData(Option);

//extractWithOnlineMethod extracts data connecting to domain URL with HTTP protocol
Data extractDataWithOnlineMethod();

//extractWithOnlineMethod extracts data obtaining html from filesystem
Data extractDataWithFSMethod();