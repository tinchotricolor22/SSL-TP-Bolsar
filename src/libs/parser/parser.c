#include "parser.h"

void init_parser(Logger debug_logger) {
    parser_debug_logger = debug_logger;
}

ParserOutput *create_parser_output(void **data_list, const int data_list_length) {
    ParserOutput *new_data = malloc(sizeof *new_data);
    new_data->data_list = data_list;
    new_data->data_list_length = data_list_length;
    return new_data;
}