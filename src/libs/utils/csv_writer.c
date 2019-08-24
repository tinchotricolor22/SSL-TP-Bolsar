#include "csv_writer.h"
#include "string.h"

void with_break_line(char *str) {
    strcat(str, "\n");
}

void remove_last_character(char *str) {
    int length = strlen(str);
    if (length > 0) {
        str[length - 1] = '\0';
    }
}