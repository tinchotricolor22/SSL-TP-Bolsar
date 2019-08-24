#include "data.h"
#include "config.h"
#include "stdlib.h"

void init_data(const Logger debug_logger) {
    data_debug_logger = debug_logger;
}

DataOutput *create_data_output(FILE* file) {
    DataOutput *p_new_output = malloc(sizeof *p_new_output);
    p_new_output->file = file;
    return p_new_output;
}
