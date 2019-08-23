#include "parsertypes.h"
#include "../domain/leader.h"
#include "../logging/logging.h"
#include "stdio.h"

#define TAGS_MAX_LENGTH 1000

#define TABLE_ACTIONS_ID "tbAcciones"

Logger parserDebugLogger;

//initParser injects dependency variables for parser that includes logger functions
void initParser(Logger debugLogger);

//parseDataFromHTML extracts data obtaining html from filesystem
ParserResult parseDataFromHTML(ParserOutput **, ParserInput*);

void fillLeadersFromTags(Tag **tags, const int tags_length, Leader **leaders, int *leaders_length);

ParserOutput *createParserOutput(Leader **leaders, const int length);

//HTML
#define TABLE_CHAR_LENGTH 40000
#define ID_LENGTH 50

void parseTagsFromHTML(FILE *file, Tag **tags, int *tags_length, const int tags_max_length, char *init_id);

char *parseHTMLFromTableID(char *ID, FILE *htmlFile);

void parseTagsFromTable(FILE *tableFile, Tag **tags, int *tags_length, const int tags_max_length);

void makeID(char *htmlID, const char *ID);

void searchPropertyID(FILE *htmlFile, char *htmlLine, const char *propertyID);

double extractDoubleValue(char* stringDouble);

void trim(const char *input, char *result);
void replace(char *input, const char character, const char replace);
int ends_with(const char *str, const char *suffix);
