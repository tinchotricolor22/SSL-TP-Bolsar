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

typedef struct Leader {
    char id[20];
    char specie[100];
    double variation;
    double purchasePrice;
    double salePrice;
    double openingPrice;
    double maxPrice;
    double minPrice;

} Leader;

//initExtractorGlobalVariables injects dependency variables for extractor that includes logger functions
void initExtractorGlobalVariables(char* userOS, char* url, char* fsPath, int(*stdLogger)(const char*,...),int(*debugLogger)(const char*,...));

//extractData is a wrapper for select the method for extract depending the option selected
Data extractData(Option);

//extractWithOnlineMethod extracts data connecting to domain URL with HTTP protocol
Data extractDataWithOnlineMethod();

//extractWithOnlineMethod extracts data obtaining html from filesystem
Data extractDataWithFSMethod();

//TODO: se hacen acá o son privadas?
Data extractHTMLFromTableID(char* tableID, FILE* htmlFile);
Data extractRowsFromTable(FILE* tableFile, char rows[100][400]);
Data extractValuesFromRowsID(char rows[400][400],char *ID);
FILE* createAuxFileFromTable(char* table);

void trim(const char *input, char *result);
void replace(char *input, const char character, const char replace);

struct Leader* new_leader();
void add_leader(struct Leader *leader);
void fillLeadersFromRows(char rows[400][400]);