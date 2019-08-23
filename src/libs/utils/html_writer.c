#include "html_writer.h"
#include "stdio.h"

void write_html_main_tags_opening(FILE *output) {
    fprintf(output, "<html><body>");
}

void write_html_main_tags_closing(FILE *output) {
    fprintf(output, "</body></html>");
}

void write_html_table_tag_opening(FILE *output) {
    fprintf(output, "<table>");
}

void write_html_table_tag_closing(FILE *output) {
    fprintf(output, "</table>");
}

void write_html_table_header_tags_opening(FILE *output) {
    fprintf(output, "<thead>");
}

void write_html_table_header_tags_closing(FILE *output) {
    fprintf(output, "</thead>");
}

void write_html_table_body_tags_opening(FILE *output) {
    fprintf(output, "<tbody>");
}

void write_html_table_body_tags_closing(FILE *output) {
    fprintf(output, "</tbody>");
}

void write_html_table_row_tags_opening(FILE *output) {
    fprintf(output, "<tr>");
}

void write_html_table_row_tags_closing(FILE *output) {
    fprintf(output, "</tr>");
}

void write_html_table_column_tags_opening(FILE *output) {
    fprintf(output, "<td>");
}

void write_html_table_column_tags_closing(FILE *output) {
    fprintf(output, "</td>");
}

void write_string_html_main_tags_opening(char *output) {
    strcat(output, "<html><body>");
}

void write_string_html_main_tags_closing(char *output) {
    strcat(output, "</body></html>");
}

void write_string_html_table_tag_opening(char *output) {
    strcat(output, "<table>");
}

void write_string_html_table_tag_closing(char *output) {
    strcat(output, "</table>");
}

void write_string_html_table_header_tags_opening(char *output) {
    strcat(output, "<thead>");
}

void write_string_html_table_header_tags_closing(char *output) {
    strcat(output, "</thead>");
}

void write_string_html_table_body_tags_opening(char *output) {
    strcat(output, "<tbody>");
}

void write_string_html_table_body_tags_closing(char *output) {
    strcat(output, "</tbody>");
}

void write_string_html_table_row_tags_opening(char *output) {
    strcat(output, "<tr>");
}

void write_string_html_table_row_tags_closing(char *output) {
    strcat(output, "</tr>");
}

void write_string_html_table_column_tags_opening(char *output) {
    strcat(output, "<td>");
}

void write_string_html_table_column_tags_closing(char *output) {
    strcat(output, "</td>");
}