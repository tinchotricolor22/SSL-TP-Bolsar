#include "../logging/logging.h"
#include "stdio.h"

#define TAGS_MAX_LENGTH 1000
#define TAG_ID 50
#define TAG_RAW_TAG 144
#define TAG_VALUE 200
#define LEADERS_MAX_LENGTH 1000

#define TABLE_ACTIONS_ID "tbAcciones"

char* UserOS;
char* URL;
char* FSPath;
Logger extractorLogger;
Logger extractorDebugLogger;

typedef struct Leader {
    char specie[100];
    double variation;
    double purchasePrice;
    double salePrice;
    double openingPrice;
    double maxPrice;
    double minPrice;

} Leader;

typedef struct Data {
    Leader** leaders;
} Data;

typedef struct Tag {
    char id[TAG_ID];
    char rawTag[TAG_RAW_TAG];
    char value[TAG_VALUE];
} Tag;

typedef Data*(*ExtractorMethod)();

//initExtractor injects dependency variables for extractor that includes logger functions
void initExtractor(Logger stdLogger,Logger debugLogger);

//extractWithOnlineMethod extracts data connecting to domain URL with HTTP protocol
Data* extractDataWithOnlineMethod();

//extractWithOnlineMethod extracts data obtaining html from filesystem
Data* extractDataWithFSMethod();

void fillLeadersFromTags(Tag **tags,const int tags_length, Leader **leaders,int *leaders_length);
Data* createData(Leader **leaders);
void add(void **elems, void *elem, int *length, const int max_length);


//HTML
#define TABLE_CHAR_LENGTH 40000
#define ID_LENGTH 50

Logger extractorHTMLDebugLogger;

void extractTagsFromHTML(FILE* file, Tag **tags, int *tags_length, const int tags_max_length,char* init_id);
char* extractHTMLFromTableID(char* ID, FILE *htmlFile);
void extractTagsFromTable(FILE* tableFile, Tag **tags, int *tags_length,const int tags_max_length);
void makeID(char* htmlID, const char* ID);
void searchPropertyID(FILE *htmlFile, char* htmlLine, const char* propertyID);

FILE* createAuxFileFromString(char* string,const char* auxPath);