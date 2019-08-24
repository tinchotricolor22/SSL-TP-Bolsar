#include "parser.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "../utils/commons.h"

#define TOTAL_COLUMNS 16

#define COLUMN_SPECIE 0
#define COLUMN_VARIATION 7
#define COLUMN_PURCHASE_PRICE 3
#define COLUMN_SALE_PRICE 4
#define COLUMN_OPENING_PRICE 8
#define COLUMN_MAX_PRICE 9
#define COLUMN_MIN_PRICE 10

#define LEADERS_MAX_LENGTH 1000

#define TABLE_OPENING_TAG "<table border=\"1\">"
#define TABLE_CLOSING_TAG "</table>"
#define COMPONENT_OPENING_TAG "<td>"
#define COMPONENT_CLOSING_TAG "</td>"

//apply_conditions return true if leader apply all conditions in list
static int apply_conditions(const Filter **filters_list, const int filters_list_length, const Leader *leader) {
    parser_debug_logger("Appliyng conditions [event:apply_conditions]");
    for (int i = 0; i < filters_list_length; i++) {
        Filter filter = filters_list[i];
        if (!filter(leader)) {
            return 0;
        }
    }
    return 1;
}

//fill_leaders_from_tags return fills leaders list depending of the tags and patterns in arguments
static void fill_leaders_from_tags(char tags_list[TAGS_MAX_LENGTH][TAG_CHAR_MAX_LENGTH], const int tags_list_length, Leader **leaders_list, int *leaders_list_length,
                                   const Filter **filters_list, const int filters_list_length) {
    parser_debug_logger("Filling leaders list from tags list [event:fill_leaders_from_tags]");
    char column[TOTAL_COLUMNS][50];
    for (int count_tags = 1; count_tags < tags_list_length; count_tags++) {
        Leader *new_leader = malloc(sizeof *new_leader);

        trim(tags_list[count_tags], tags_list[count_tags]);

        sscanf(tags_list[count_tags], "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;]", column[0], column[1], column[2], column[3], column[4], column[5], column[6], column[7], column[8], column[9], column[10], column[11], column[12], column[13], column[14], column[15]);
        strcpy(new_leader->specie, column[COLUMN_SPECIE]);

        new_leader->variation = extract_double_value(column[COLUMN_VARIATION]);
        new_leader->purchase_price = extract_double_value(column[COLUMN_PURCHASE_PRICE]);
        new_leader->sale_price = extract_double_value(column[COLUMN_SALE_PRICE]);
        new_leader->opening_price = extract_double_value(column[COLUMN_OPENING_PRICE]);
        new_leader->max_price = extract_double_value(column[COLUMN_MAX_PRICE]);
        new_leader->min_price = extract_double_value(column[COLUMN_MIN_PRICE]);

        if (apply_conditions(filters_list, filters_list_length, new_leader)) {
            add(leaders_list, new_leader, leaders_list_length, LEADERS_MAX_LENGTH);
        }
    }
}

ParserResult parse_data_from_html(ParserOutput **data_list, const ParserInput *parser_input) {
    parser_debug_logger("Parsing data from html to fills leaders and return parser output [event:parse_data_from_html]");

    char tags_list[TAGS_MAX_LENGTH][TAG_CHAR_MAX_LENGTH];
    int tags_list_length = 0;

    parse_table_from_html_file(parser_input->file, tags_list, &tags_list_length,
                               TAGS_MAX_LENGTH, TABLE_OPENING_TAG, TABLE_CLOSING_TAG, COMPONENT_OPENING_TAG, COMPONENT_CLOSING_TAG);

    Leader **leaders_list = malloc(LEADERS_MAX_LENGTH * sizeof leaders_list[0]);
    int leaders_list_length = 0;
    fill_leaders_from_tags(tags_list, tags_list_length, leaders_list, &leaders_list_length, parser_input->filters_list, parser_input->filters_list_length);

    parser_debug_logger("Creating parser output [event:parse_data_from_html]");
    *data_list = create_parser_output(leaders_list, leaders_list_length);
    return PARSER_RESULT_OK;
}


