#include "parser.h"
#include "../config/config.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "../utils/commons.h"

void parseTagsFromHTML(FILE *file, Tag **tags, int *tags_length, const int tags_max_length, char *init_id) {
    parserDebugLogger("Starting to process htmlFile [event:parseTagsFromHTML]");
    char *table = parseHTMLFromTableID(init_id, file);
    FILE *tableFile = createAuxFileFromString(table, getAuxTableFileName());

    parseTagsFromTable(tableFile, tags, tags_length, tags_max_length);
    fclose(tableFile);
}

char *parseHTMLFromTableID(char *ID, FILE *htmlFile) {
    parserDebugLogger("Starting to extract table from htmlFile [event:parseHTMLFromTableID]");
    char htmlLine[TABLE_CHAR_LENGTH], propertyID[ID_LENGTH];

    makeID(propertyID, ID);
    searchPropertyID(htmlFile, htmlLine, propertyID);

    return htmlLine;
}

void parseTagsFromTable(FILE *tableFile, Tag **tags, int *tags_length, const int tags_max_length) {
    parserDebugLogger("Starting to extract tags from table file [event:parseTagsFromTable]");
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
    parserDebugLogger("Creating aux file to iterate table in path %s [event:createAuxFileFromString]", auxPath);
    FILE *file = fopen(auxPath, "w+");

    if (file == NULL) {
        parserDebugLogger("ERROR: Cannot open file in path: %s [event:createAuxFileFromString]", auxPath);
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
    parserDebugLogger("Searching %s table", propertyID);
    while (!feof(htmlFile)) {
        parserDebugLogger("entra al while");
        fgets(htmlLine, 40000, htmlFile);
        if (strstr(htmlLine, propertyID)) {
            parserDebugLogger("%s table founded", propertyID);
            break;
        }
    }
}