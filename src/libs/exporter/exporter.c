#include "exporter.h"
#include "../config/config.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

void init_exporter(const Logger debug_logger) {
    exporter_debug_logger = debug_logger;
}

ExporterColumns *
build_leader_columns(const int specie, const int variation, const int purchase_price, const int sale_price,
                     const int opening_price, const int max_price, const int min_price) {
    LeaderColumns *leader_columns = malloc(sizeof(*leader_columns));
    leader_columns->specie = specie;
    leader_columns->variation = variation;
    leader_columns->purchase_price = purchase_price;
    leader_columns->sale_price = sale_price;
    leader_columns->opening_price = opening_price;
    leader_columns->max_price = max_price;
    leader_columns->min_price = min_price;
    return leader_columns;
}

void output_path_with_extension(char *output, const char *extension) {
    strcpy(output, g_config.exporter_output_path);
    strcat(output, extension);
}