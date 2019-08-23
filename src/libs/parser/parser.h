#ifndef PARSER_HEADER
#define PARSER_HEADER

#include "parser.h"
#include "../domain/leader.h"
#include "../logging/logging.h"
#include "../filter/filter.h"
#include "stdio.h"

#define TAGS_MAX_LENGTH 100
#define TAG_CHAR_MAX_LENGTH 1000

#define TABLE_ACTIONS_ID "<table border=\"1\">"
#define TABLE_CLOSE_TAGS "</table>"

#define PARSER_RESULT_OK 0
#define PARSER_RESULT_ERROR 1

#define TAG_ID 200
#define TAG_RAW_TAG 200
#define TAG_VALUE 200

Logger parserDebugLogger;

typedef int ParserResult;

typedef struct ParserOutput {
    Leader **leaders;
    int leaders_length;
} ParserOutput;

typedef struct ParserInput {
    FILE* file;
    Filter** filters;
    int filters_length;
    //Formatter** formatter;
} ParserInput;

//TODO: Esto hacerlo en un type de html
typedef struct Tag {
    char id[TAG_ID];
    char rawTag[TAG_RAW_TAG];
    char value[TAG_VALUE];
} Tag;

typedef ParserResult(*ParserMethod)(ParserOutput **, ParserInput *);

/********** PUBLIC **********/
//initParser injects dependency variables for parser that includes logger functions
void initParser(Logger debugLogger);

ParserResult parseDataFromHTML(ParserOutput **, ParserInput*);
/***************************/


//HTML
void parseTagsFromHTML(FILE *file, char tdTags[TAGS_MAX_LENGTH][TAG_CHAR_MAX_LENGTH], int *tags_length, const int tags_max_length);
void searchTable(FILE *htmlFile, char tags[TAGS_MAX_LENGTH][TAG_CHAR_MAX_LENGTH], int *tags_current);
void searchTag(FILE *htmlFile, char *htmlLine, char tags[TAGS_MAX_LENGTH][TAG_CHAR_MAX_LENGTH], int *tags_current, const char *tagToSearch,const char *closeTag);

#endif