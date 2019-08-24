#include "parser.h"
#include "../config/config.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "../utils/commons.h"

//search_tags search tags pattern opening in html file. When founds it, adds tag in list, replacing tags pattern in string.
//Ends when it founds break_pattern_tag
static void search_tags(FILE *p_html_file, char tags_list[TAGS_MAX_LENGTH][TAG_CHAR_MAX_LENGTH], int *p_tags_list_current_length, const int tags_list_max_length,
                        const char *html_line, const char *component_pattern_opening, const char *component_pattern_closing,
                        const char *break_pattern_tag) {
    parser_debug_logger("Searching tags with patterns of opening tag %s and closing %s and break pattern tag %s [event:search_tags]",
                        component_pattern_opening, component_pattern_closing, break_pattern_tag);
    while (!feof(p_html_file) && *p_tags_list_current_length < tags_list_max_length) {
        fgets(html_line, TAG_CHAR_MAX_LENGTH, p_html_file);
        if (strstr(html_line, component_pattern_opening)) {

            char *replace;
            replace = str_replace(html_line, component_pattern_opening, "");
            replace = str_replace(replace, component_pattern_closing, ";");
            strcpy(tags_list[*p_tags_list_current_length], replace);
            free(replace);

            (*p_tags_list_current_length)++;
        } else if (strstr(html_line, break_pattern_tag)) {
            break;
        }
    }
}

//search_table search table pattern opening in html file. When it founds, call to search tags with component patterns and table closing pattern
static void search_table(FILE *p_html_file, char tags_list[TAGS_MAX_LENGTH][TAG_CHAR_MAX_LENGTH], int *p_tags_list_current_length, const int tags_list_max_length,
                         const char *table_pattern_opening, const char *table_pattern_closing,
                         const char *component_pattern_opening, const char *component_pattern_closing) {
    parser_debug_logger("Searching table with patterns of opening %s and closing %s [event:search_table]", table_pattern_opening, table_pattern_closing);

    char html_line[TAG_CHAR_MAX_LENGTH];
    while (!feof(p_html_file)) {
        fgets(html_line, TAG_CHAR_MAX_LENGTH, p_html_file);

        if (strstr(html_line, table_pattern_opening)) {
            search_tags(p_html_file, tags_list, p_tags_list_current_length, tags_list_max_length, html_line,
                        component_pattern_opening, component_pattern_closing, table_pattern_closing);
            break;
        }
    }

}

void parse_table_from_html_file(FILE *p_html_file, char tags_list[TAGS_MAX_LENGTH][TAG_CHAR_MAX_LENGTH], int *p_tags_list_current_length, const int tags_list_max_length,
                                const char *table_pattern_opening, const char *table_pattern_closing,
                                const char *component_pattern_opening,
                                const char *component_pattern_closing) {
    parser_debug_logger("Parsing html file [event:parse_table_from_html_file]");
    search_table(p_html_file, tags_list, p_tags_list_current_length, tags_list_max_length, table_pattern_opening, table_pattern_closing,
                 component_pattern_opening, component_pattern_closing);
}