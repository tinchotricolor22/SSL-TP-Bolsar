#ifndef PARSER_HEADER
#define PARSER_HEADER

#include "parser.h"
#include "../domain/leader.h"
#include "../logging/logging.h"
#include "../filter/filter.h"
#include "stdio.h"

#define TAGS_MAX_LENGTH 100
#define TAG_CHAR_MAX_LENGTH 1000

#define PARSER_RESULT_OK 0
#define PARSER_RESULT_ERROR 1

//parser_debug_logger is logger for parser
Logger parser_debug_logger;

//ParserResult represents the result of parser methods
typedef int ParserResult;

//ParserOutput represents the output of parser methods
typedef struct ParserOutput {
    void **data_list;
    int data_list_length;
} ParserOutput;

//ParserInput represents the input of parser methods
typedef struct ParserInput {
    FILE *file;
    Filter **filters_list;
    int filters_list_length;
} ParserInput;


//ParserMethod represents the parser methods
typedef ParserResult(*ParserMethod)(ParserOutput **, ParserInput *);

//init_parser injects dependency variables for parser that includes logger functions
void init_parser(Logger);

//create_parser_output creates parser output from data_list
ParserOutput *create_parser_output(void **, const int);

//parse_data_from_html parse html from input file and returns and output with domain class filled
ParserResult parse_data_from_html(ParserOutput **, const ParserInput *);

/***********HTML***********/
//parse_table_from_html_file search table in html file and fill tags_list
void parse_table_from_html_file(FILE *, char tags_list[TAGS_MAX_LENGTH][TAG_CHAR_MAX_LENGTH], int *, const int, const char *, const char *, const char *, const char *);

#endif