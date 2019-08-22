#include "parsertypes.h"
#include "../domain/leader.h"
#include "../logging/logging.h"
#include "stdio.h"

#define TAGS_MAX_LENGTH 100
#define TAG_CHAR_MAX_LENGTH 1000

#define TABLE_ACTIONS_ID "<table border=\"1\">"
#define TABLE_CLOSE_TAGS "</table>"

Logger parserDebugLogger;

//initParser injects dependency variables for parser that includes logger functions
void initParser(Logger debugLogger);

//parseDataFromHTML extracts data obtaining html from filesystem
ParserResult parseDataFromHTML(ParserOutput **, ParserInput*);

//void fillLeadersFromTags(Tag **tags, const int tags_length, Leader **leaders, int *leaders_length);
void fillLeadersFromTagsStr(char tags[TAGS_MAX_LENGTH][TAG_CHAR_MAX_LENGTH], const int tags_length, Leader **leaders, int *leaders_length);

ParserOutput *createParserOutput(Leader **leaders, const int length);

//HTML
#define TABLE_CHAR_LENGTH 40000
#define ID_LENGTH 50

void parseTagsFromHTML(FILE *file, char tdTags[TAGS_MAX_LENGTH][TAG_CHAR_MAX_LENGTH], int *tags_length, const int tags_max_length);
void parseTagsFromTable(FILE *tableFile, Tag **tags, int *tags_length, const int tags_max_length);

void searchTable(FILE *htmlFile, char tags[TAGS_MAX_LENGTH][TAG_CHAR_MAX_LENGTH], int *tags_current);
void searchTag(FILE *htmlFile, char *htmlLine, char tags[TAGS_MAX_LENGTH][TAG_CHAR_MAX_LENGTH], int *tags_current, const char *tagToSearch,const char *closeTag);

double extractDoubleValue(char* stringDouble);

void trim(const char *input, char *result);
void replace(char *input, const char character, const char replace);
int ends_with(const char *str, const char *suffix);
char *str_replace(char *orig, char *rep, char *with);