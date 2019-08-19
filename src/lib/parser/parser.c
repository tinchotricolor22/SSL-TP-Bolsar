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
#define SUFFIX_PURCHASE_PRICE "3_PU"
#define SUFFIX_SALE_PRICE "3_PV"
#define SUFFIX_OPENING_PRICE "3_PAPE"
#define SUFFIX_MAX_PRICE "3_PMAX"
#define SUFFIX_MIN_PRICE "3_PMIN"

void initParser(Logger debugLogger) {
    parserDebugLogger = debugLogger;
}

ParserResult parseDataFromHTML(ParserOutput **data, ParserInput* parserInput) {
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
    parserDebugLogger("Starting to fill leaders [event:fillLeadersFromRows]");
    Leader *actualProcessingLeader;

    parserDebugLogger("tags length: %d [event:fillLeadersFromRows]", tags_length);

    for (int countTags = 0; countTags < tags_length; countTags++) {
        if (!strcmp(tags[countTags]->id, ID_SPECIE)) {
            parserDebugLogger("matchea el value: %s \n", tags[countTags]->value);
            Leader *newLeader = malloc(sizeof *newLeader);
            //char* specie = "specie_test";//extractStringValue(tags[countTags]->value);
            strcpy(newLeader->specie, "specie_test");

            add(leaders, newLeader, leaders_length, LEADERS_MAX_LENGTH);
            actualProcessingLeader = newLeader;
        } else if (strstr(tags[countTags]->id, SUFFIX_VARIATION)) {
            parserDebugLogger("variation matchea el value: %s \n", tags[countTags]->value);
            double value = 1.00f; //extractVariationValue(rows[tags[countTags]->value]);
            actualProcessingLeader->variation = value;
        } else if (strstr(tags[countTags]->id, SUFFIX_PURCHASE_PRICE)) {
            parserDebugLogger("purchase matchea el value: %s \n", tags[countTags]->value);
            double value = 1.00; //extractDoubleValue(rows[tags[countTags]->value]);
            actualProcessingLeader->purchasePrice = value;
        } else if (strstr(tags[countTags]->id, SUFFIX_SALE_PRICE)) {
            parserDebugLogger("sale matchea el value: %s \n", tags[countTags]->value);
            double value = 1.00f; //extractDoubleValue(rows[tags[countTags]->value]);
            actualProcessingLeader->salePrice = value;
        } else if (strstr(tags[countTags]->id, SUFFIX_OPENING_PRICE)) {
            parserDebugLogger("opening matchea el value: %s \n", tags[countTags]->value);
            double value = 0.00f; //extractDoubleValue(rows[tags[countTags]->value]);
            actualProcessingLeader->openingPrice = value;
        } else if (strstr(tags[countTags]->id, SUFFIX_MAX_PRICE)) {
            parserDebugLogger("max price matchea el value: %s \n", tags[countTags]->value);
            double value = 1.00f; //extractDoubleValue(rows[tags[countTags]->value]);
            actualProcessingLeader->maxPrice = value;
        } else if (strstr(tags[countTags]->id, SUFFIX_MIN_PRICE)) {
            parserDebugLogger("min price matchea el value: %s \n", tags[countTags]->value);
            double value = 1.00f; //extractDoubleValue(rows[tags[countTags]->value]);
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

ParserInput* buildParserInputFromDataOutput(DataOutput* dataOutput){
    ParserInput *newInput = malloc(sizeof *newInput);
    newInput->file = dataOutput->file;
    return newInput;
}

/*ParserOutput* extractValuesFromRowsID(char rows[400][400],char *id_suffix){
    parserDebugLogger("Starting to extract values from row ID [event:extractRowsFromTable]");
    void* ret[400];

    for(int countRows=0, retCount = 0; countRows < 400; countRows++){
        char identifier[10],prefix[50],suffix[50];

        sscanf(rows[countRows],"%[^\"]\"%[^_]_%[^\"]",identifier,prefix,suffix);
        if(strstr(suffix,id_suffix)){
            char rest[100];
            char stringDouble[10];
            //TODO: acá habría que mandar una function generic
            sscanf(rows[countRows],"%[^>]>%[^&]",rest,stringDouble);

            trim(stringDouble,stringDouble);
            replace(stringDouble,',','.');

            double result = atof(stringDouble);
            printf("resultado: %f   \n",result);
        }
    }
    return "";
}

void trim(const char *input, char *result)
{
  int i, j = 0;
  for (i = 0; input[i] != '\0'; i++) {
    if (!isspace((unsigned char) input[i])) {
      result[j++] = input[i];
    }
  }
  result[j] = '\0';
}

void replace(char *input, const char character, const char replace)
{
  for (int i = 0; input[i] != '\0'; i++) {
    if (input[i] == character){
        input[i] = replace;
    }
  }
}*/