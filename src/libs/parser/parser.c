#include "parser.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "../utils/commons.h"
#include "../logging/logging.h"

#define COLUMN_SPECIE 0
#define COLUMN_VARIATION 7
#define COLUMN_PURCHASE_PRICE 3
#define COLUMN_SALE_PRICE 4
#define COLUMN_OPENING_PRICE 8
#define COLUMN_MAX_PRICE 9
#define COLUMN_MIN_PRICE 10

/************** PRIVATE **************/
static ParserOutput *createParserOutput(Leader **leaders, const int length);
static void fillLeadersFromTagsStr(char tags[TAGS_MAX_LENGTH][TAG_CHAR_MAX_LENGTH], const int tags_length, Leader **leaders, int *leaders_length, Filter** filters, const int filters_length);
static FilterResult apply_conditions(Filter** filters, const int filters_length,Leader *leader);

/************************************/
void initParser(Logger debugLogger) {
    parserDebugLogger = debugLogger;
}

ParserResult parseDataFromHTML(ParserOutput **data, ParserInput *parserInput) {
    char tags[TAGS_MAX_LENGTH][TAG_CHAR_MAX_LENGTH];
    int tags_length = 0;

    parseTagsFromHTML(parserInput->file, tags,&tags_length, TAGS_MAX_LENGTH);

    Leader **leaders = malloc(LEADERS_MAX_LENGTH * sizeof leaders[0]);
    int leaders_length = 0;
    fillLeadersFromTagsStr(tags, tags_length, leaders, &leaders_length, parserInput->filters, parserInput->filters_length);

    *data = createParserOutput(leaders, leaders_length);
    return PARSER_RESULT_OK;
}

static void fillLeadersFromTagsStr(char tags[TAGS_MAX_LENGTH][TAG_CHAR_MAX_LENGTH], const int tags_length, Leader **leaders, int *leaders_length, Filter** filters, const int filters_length) {
    char column[16][50];
    for (int countTags = 1; countTags < tags_length; countTags++) {
        Leader *newLeader = malloc(sizeof *newLeader);
        trim(tags[countTags],tags[countTags]);
        sscanf(tags[countTags], "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;]", column[0],column[1],column[2],column[3], column[4],column[5],column[6],column[7], column[8],column[9],column[10],column[11], column[12],column[13],column[14],column[15]);
        strcpy(newLeader->specie, column[COLUMN_SPECIE]);
        newLeader->variation = extract_double_value(column[COLUMN_VARIATION]);
        newLeader->purchase_price= extract_double_value(column[COLUMN_PURCHASE_PRICE]);
        newLeader->sale_price= extract_double_value(column[COLUMN_SALE_PRICE]);
        newLeader->opening_price= extract_double_value(column[COLUMN_OPENING_PRICE]);
        newLeader->max_price= extract_double_value(column[COLUMN_MAX_PRICE]);
        newLeader->min_price = extract_double_value(column[COLUMN_MIN_PRICE]);

        if (apply_conditions(filters,filters_length,newLeader)) {
            add(leaders, newLeader, leaders_length, LEADERS_MAX_LENGTH);
        }
    }
}

static ParserOutput *createParserOutput(Leader **leaders, const int length) {
    ParserOutput *newData = malloc(sizeof *newData);
    newData->leaders = leaders;
    newData->leaders_length = length;
    return newData;
}

static int apply_conditions(Filter** filters, const int filters_length,Leader *leader){
    for(int i = 0; i< filters_length ; i ++){
        Filter filter = filters[i];
        if(!filter(leader)){
            return 0;
        }
    }
    return 1;
}
