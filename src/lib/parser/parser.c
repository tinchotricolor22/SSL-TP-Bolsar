#include "parser.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"
#include "../utils/commons.h"
#include "../logging/logging.h"
#include "../config/config.h"

#define ID_SPECIE "spPopSimbolo"
#define SUFFIX_VARIATION "3_VAR"
#define SUFFIX_PURCHASE_PRICE "3_PC"
#define SUFFIX_SALE_PRICE "3_PV"
#define SUFFIX_OPENING_PRICE "3_PAPE"
#define SUFFIX_MAX_PRICE "3_PMAX"
#define SUFFIX_MIN_PRICE "3_PMIN"

void initParser(Logger debugLogger) {
    parserDebugLogger = debugLogger;
}

ParserResult parseDataFromHTML(ParserOutput **data, ParserInput *parserInput) {
    Tag **tags = malloc(TAGS_MAX_LENGTH * sizeof tags[0]);
    int tags_length = 0;

    parseTagsFromHTML(parserInput->file, tags, &tags_length, TAGS_MAX_LENGTH, TABLE_ACTIONS_ID);
    fclose(parserInput->file);

    Leader **leaders = malloc(LEADERS_MAX_LENGTH * sizeof leaders[0]);
    int leaders_length = 0;
    fillLeadersFromTags(tags, tags_length, leaders, &leaders_length);

    *data = createParserOutput(leaders, leaders_length);
    return PARSER_RESULT_OK;
}

void fillLeadersFromTags(Tag **tags, const int tags_length, Leader **leaders, int *leaders_length) {
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
}

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