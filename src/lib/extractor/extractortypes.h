#ifndef EXTRACTOR_TYPES_HEADER
#define EXTRACTOR_TYPES_HEADER

#include "../domain/leader.h"

#define EXTRACTOR_RESULT_OK 0
#define EXTRACTOR_RESULT_ERROR_OPENING_FILE 1
#define EXTRACTOR_RESULT_ERROR 2

#define TAG_ID 200
#define TAG_RAW_TAG 200
#define TAG_VALUE 200


typedef int ExtractorResult;

typedef struct Data {
    Leader **leaders;
    int leaders_length;
} Data;

typedef struct Tag {
    char id[TAG_ID];
    char rawTag[TAG_RAW_TAG];
    char value[TAG_VALUE];
} Tag;

typedef ExtractorResult(*ExtractorMethod)(Data **);

#endif