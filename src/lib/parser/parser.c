#include "parser.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"
#include "../utils/commons.h"
#include "../logging/logging.h"
#include "../config/config.h"

#define COLUMN_SPECIE 0
#define COLUMN_VARIATION 7
#define COLUMN_PURCHASE_PRICE 3
#define COLUMN_SALE_PRICE 4
#define COLUMN_OPENING_PRICE 8
#define COLUMN_MAX_PRICE 9
#define COLUMN_MIN_PRICE 10

void initParser(Logger debugLogger) {
    parserDebugLogger = debugLogger;
}

ParserResult parseDataFromHTML(ParserOutput **data, ParserInput *parserInput) {
    /*Tag **tags = malloc(TAGS_MAX_LENGTH * sizeof tags[0]);
    int tags_length = 0;*/

    char tags[TAGS_MAX_LENGTH][TAG_CHAR_MAX_LENGTH];
    int tags_length = 0;

    parseTagsFromHTML(parserInput->file, tags,&tags_length, TAGS_MAX_LENGTH);

    Leader **leaders = malloc(LEADERS_MAX_LENGTH * sizeof leaders[0]);
    int leaders_length = 0;
    fillLeadersFromTagsStr(tags, tags_length, leaders, &leaders_length);

    *data = createParserOutput(leaders, leaders_length);
    return PARSER_RESULT_OK;
}

void fillLeadersFromTagsStr(char tags[TAGS_MAX_LENGTH][TAG_CHAR_MAX_LENGTH], const int tags_length, Leader **leaders, int *leaders_length) {
    char column[16][50];
    for (int countTags = 1; countTags < tags_length; countTags++) {
        Leader *newLeader = malloc(sizeof *newLeader);
        trim(tags[countTags],tags[countTags]);
        sscanf(tags[countTags], "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;]", column[0],column[1],column[2],column[3], column[4],column[5],column[6],column[7], column[8],column[9],column[10],column[11], column[12],column[13],column[14],column[15]);
        strcpy(newLeader->specie, column[COLUMN_SPECIE]);
        newLeader->variation = extractDoubleValue(column[COLUMN_VARIATION]);
        newLeader->purchasePrice= extractDoubleValue(column[COLUMN_PURCHASE_PRICE]);
        newLeader->salePrice=extractDoubleValue(column[COLUMN_SALE_PRICE]);
        newLeader->openingPrice= extractDoubleValue(column[COLUMN_OPENING_PRICE]);
        newLeader->maxPrice= extractDoubleValue(column[COLUMN_MAX_PRICE]);
        newLeader->minPrice = extractDoubleValue(column[COLUMN_MIN_PRICE]);

        add(leaders, newLeader, leaders_length, LEADERS_MAX_LENGTH);
    }
}

/*void fillLeadersFromTags(Tag **tags, const int tags_length, Leader **leaders, int *leaders_length) {
    parserDebugLogger("Starting to fill %d leaders [event:fillLeadersFromRows]",tags_length);
    Leader *actualProcessingLeader;

    for (int countTags = 0; countTags < tags_length; countTags++) {
        if (!strcmp(tags[countTags]->id, ID_SPECIE)) {
            Leader *newLeader = malloc(sizeof *newLeader);
            char* specie = tags[countTags]->value;
            strcpy(newLeader->specie, specie);

            add(leaders, newLeader, leaders_length, LEADERS_MAX_LENGTH);
            actualProcessingLeader = newLeader;
        } else if (ends_with(tags[countTags]->id, SUFFIX_VARIATION)) {
            double value = extractDoubleValue(tags[countTags]->value);
            actualProcessingLeader->variation = value;
        } else if (ends_with(tags[countTags]->id, SUFFIX_PURCHASE_PRICE)) {
            double value = extractDoubleValue(tags[countTags]->value);
            actualProcessingLeader->purchasePrice = value;
        } else if (ends_with(tags[countTags]->id, SUFFIX_SALE_PRICE)) {
            double value = extractDoubleValue(tags[countTags]->value);
            actualProcessingLeader->salePrice = value;
        } else if (ends_with(tags[countTags]->id, SUFFIX_OPENING_PRICE)) {
            double value = extractDoubleValue(tags[countTags]->value);
            actualProcessingLeader->openingPrice = value;
        } else if (ends_with(tags[countTags]->id, SUFFIX_MAX_PRICE)) {
            double value = extractDoubleValue(tags[countTags]->value);
            actualProcessingLeader->maxPrice = value;
        } else if (ends_with(tags[countTags]->id, SUFFIX_MIN_PRICE)) {
            double value = extractDoubleValue(tags[countTags]->value);
            actualProcessingLeader->minPrice = value;
        }
    }
}*/

ParserOutput *createParserOutput(Leader **leaders, const int length) {
    ParserOutput *newData = malloc(sizeof *newData);
    newData->leaders = leaders;
    newData->leaders_length = length;
    return newData;
}

ParserInput *buildParserInputFromDataOutput(DataOutput *dataOutput) {
    ParserInput *newInput = malloc(sizeof *newInput);
    newInput->file = dataOutput->file;
    return newInput;
}

double extractDoubleValue(char *stringDouble) {
    trim(stringDouble, stringDouble);
    replace(stringDouble, ',', '.');

    return atof(stringDouble);
}

void trim(const char *input, char *result) {
    int i, j = 0;
    for (i = 0; input[i] != '\0'; i++) {
        if (!isspace((unsigned char) input[i])) {
            result[j++] = input[i];
        }
    }
    result[j] = '\0';
}

void replace(char *input, const char character, const char replace) {
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == character) {
            input[i] = replace;
        }
    }
}

int ends_with(const char *str, const char *suffix)
{
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

// You must free the result if result is non-NULL.
char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}
