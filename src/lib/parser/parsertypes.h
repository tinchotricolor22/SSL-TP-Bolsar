#ifndef PARSER_TYPES_HEADER
#define PARSER_TYPES_HEADER

#include "../domain/leader.h"

#define PARSER_RESULT_OK 0
#define PARSER_RESULT_ERROR_OPENING_FILE 1
#define PARSER_RESULT_ERROR 2

#define TAG_ID 200
#define TAG_RAW_TAG 200
#define TAG_VALUE 200


typedef int ParserResult;

typedef struct Data {
    Leader **leaders;
    int leaders_length;
} Data;

//TODO: Esto hacerlo en un type de html
typedef struct Tag {
    char id[TAG_ID];
    char rawTag[TAG_RAW_TAG];
    char value[TAG_VALUE];
} Tag;

typedef ParserResult(*ParserMethod)(Data **);

#endif