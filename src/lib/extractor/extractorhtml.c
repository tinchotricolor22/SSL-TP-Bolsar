#include "extractor.h"
#include "../config/config.h"
#include "stdlib.h"
#include "string.h"
#include "../utils/commons.h"

void extractTagsFromHTML(FILE *file, Tag **tags, int *tags_length, const int tags_max_length, char *init_id) {
    extractorDebugLogger("Starting to process htmlFile [event:processHTMLExtractor]");
    char *table = extractHTMLFromTableID(init_id, file);
    FILE *tableFile = createAuxFileFromString(table, getAuxTableFileName());

    extractTagsFromTable(tableFile, tags, tags_length, tags_max_length);
    fclose(tableFile);
}

char *extractHTMLFromTableID(char *ID, FILE *htmlFile) {
    extractorDebugLogger("Starting to extract table from htmlFile [event:extractHTMLFromTableID]");
    char htmlLine[TABLE_CHAR_LENGTH], propertyID[ID_LENGTH];

    makeID(propertyID, ID);
    searchPropertyID(htmlFile, htmlLine, propertyID);

    return htmlLine;
}

void extractTagsFromTable(FILE *tableFile, Tag **tags, int *tags_length, const int tags_max_length) {
    extractorDebugLogger("Starting to extract tags from table file [event:extractTagsFromTable]");
    char rawTag[TAG_RAW_TAG], value[TAG_VALUE];

    //volvemos al principio del file
    rewind(tableFile);
    while (fscanf(tableFile, "%[^>]>%[^<]<", rawTag, value) != EOF) {
        char identifierTag[10], identifierValue[TAG_ID];

        sscanf(rawTag, "%[^=]=\"%[^\"]\"", identifierTag, identifierValue);

        Tag *newTag = malloc(sizeof *newTag);

        strcpy(newTag->id, identifierValue);
        strcpy(newTag->rawTag, rawTag);
        strcpy(newTag->value, value);

        add(tags, newTag, tags_length, tags_max_length);
    }
}

FILE *createAuxFileFromString(char *string, const char *auxPath) {
    extractorDebugLogger("Creating aux file to iterate table in path %s [event:createAuxFileFromString]", auxPath);
    FILE *file = fopen(auxPath, "w+");

    if (file == NULL) {
        extractorDebugLogger("ERROR: Cannot open file in path: %s [event:createAuxFileFromString]", auxPath);
        return file;
    }

    fprintf(file, "%s", string);
    return file;
}

void makeID(char *htmlID, const char *ID) {
    char *htmlIDAux = "id=";
    strcat(htmlID, htmlIDAux);
    strcat(htmlID, "\"");
    strcat(htmlID, ID);
    strcat(htmlID, "\"");
}

void searchPropertyID(FILE *htmlFile, char *htmlLine, const char *propertyID) {
    extractorDebugLogger("Searching %s table", propertyID);
    while (!feof(htmlFile)) {
        fgets(htmlLine, 40000, htmlFile);
        if (strstr(htmlLine, propertyID)) {
            extractorDebugLogger("%s table founded", propertyID);
            break;
        }
    }
}