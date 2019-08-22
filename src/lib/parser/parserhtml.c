#include "parser.h"
#include "../config/config.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "../utils/commons.h"

void parseTagsFromHTML(FILE *file, char tdTags[TAGS_MAX_LENGTH][TAG_CHAR_MAX_LENGTH], int *tags_length, const int tags_max_length) {
    parserDebugLogger("Starting to process htmlFile [event:parseTagsFromHTML]");
    searchTable(file,tdTags,tags_length);

//    parseTagsFromTable(tableFile, tags, tags_length, tags_max_length);
}

/*void parseTagsFromTable(FILE *tableFile, Tag **tags, int *tags_length, const int tags_max_length) {
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
*/

void searchTable(FILE *htmlFile, char tags[TAGS_MAX_LENGTH][TAG_CHAR_MAX_LENGTH], int *tags_current) {
    parserDebugLogger("Searching table");
    char htmlLine[TAG_CHAR_MAX_LENGTH];
    while (!feof(htmlFile)) {
        fgets(htmlLine, TAG_CHAR_MAX_LENGTH, htmlFile);
        if (strstr(htmlLine, "<table border=\"1\">")) {
            searchTag(htmlFile, htmlLine, tags, tags_current, "<td>", "</table>");
            break;
        }
    }

}

void searchTag(FILE *htmlFile, char *htmlLine, char tags[TAGS_MAX_LENGTH][TAG_CHAR_MAX_LENGTH], int *tags_current, const char *tagToSearch,
               const char *closeTag) {
    while (!feof(htmlFile)) {
        fgets(htmlLine, TAG_CHAR_MAX_LENGTH, htmlFile);
        if (strstr(htmlLine, tagToSearch)) {
            char *replacement;
            replacement = str_replace(htmlLine, "<td>", "");
            replacement = str_replace(replacement, "</td>", ";");
            strcpy(tags[*tags_current],replacement);
            free(replacement);
            //free(htmlLine);
            (*tags_current)++;
        } else if (strstr(htmlLine, closeTag)) {
            break;
        }
    }
}