#ifndef HTML_WRITER_HEADER
#define HTML_WRITER_HEADER

#include "stdio.h"

//HTML Tags File
void write_html_main_tags_opening(FILE *);

void write_html_main_tags_closing(FILE *);

void write_html_table_tag_opening(FILE *);

void write_html_table_tag_closing(FILE *);

void write_html_table_body_tags_opening(FILE *);

void write_html_table_body_tags_closing(FILE *);

void write_string_html_table_header_tags_opening(char *);

void write_string_html_table_header_tags_closing(char *);

void write_string_html_table_row_tags_opening(char *);

void write_string_html_table_row_tags_closing(char *);

void write_string_html_table_column_tags_opening(char *);

void write_string_html_table_column_tags_closing(char *);

#endif
