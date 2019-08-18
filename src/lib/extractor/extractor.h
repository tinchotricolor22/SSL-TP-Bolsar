#include "extractortypes.h"
#include "../domain/leader.h"
#include "../logging/logging.h"
#include "stdio.h"

#define TAGS_MAX_LENGTH 1000
#define LEADERS_MAX_LENGTH 1000

#define TABLE_ACTIONS_ID "tbAcciones"

char* UserOS;
char* URL;
char* FSPath;
Logger extractorLogger;
Logger extractorDebugLogger;

//initExtractor injects dependency variables for extractor that includes logger functions
void initExtractor(Logger stdLogger,Logger debugLogger);

//extractWithOnlineMethod extracts data connecting to domain URL with HTTP protocol
ExtractorResult extractDataWithOnlineMethod(Data**);

//extractWithOnlineMethod extracts data obtaining html from filesystem
ExtractorResult extractDataWithFSMethod(Data**);

void fillLeadersFromTags(Tag **tags,const int tags_length, Leader **leaders,int *leaders_length);
Data* createData(Leader **leaders,const int length);

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