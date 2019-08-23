#include "exporter.h"
#include "../utils/csv_writer.h"
#include "string.h"
#include "stdio.h"
#include "config.h"

//with_csv_delimiter concats csv delimiter from config
static void with_csv_delimiter(char *p_str) {
    strcat(p_str, g_config.csv_delimiter);
}

//build_leader_csv_headers assigns headers depending of the colums of user
static void build_leader_csv_headers(ExporterColumns *p_leader_columns, char *p_headers) {
    strcpy(p_headers, "");
    if (p_leader_columns->specie) {
        strcat(p_headers, LEADER_SPECIE_HEADER);
        with_csv_delimiter(p_headers);
    }

    if (p_leader_columns->variation) {
        strcat(p_headers, LEADER_VARIATION_HEADER);
        with_csv_delimiter(p_headers);
    }

    if (p_leader_columns->purchase_price) {
        strcat(p_headers, LEADER_PURCHASE_PRICE_HEADER);
        with_csv_delimiter(p_headers);
    }

    if (p_leader_columns->sale_price) {
        strcat(p_headers, LEADER_SALE_PRICE_HEADER);
        with_csv_delimiter(p_headers);
    }

    if (p_leader_columns->opening_price) {
        strcat(p_headers, LEADER_OPENING_PRICE_HEADER);
        with_csv_delimiter(p_headers);
    }

    if (p_leader_columns->max_price) {
        strcat(p_headers, LEADER_MAX_PRICE_HEADER);
        with_csv_delimiter(p_headers);
    }

    if (p_leader_columns->min_price) {
        strcat(p_headers, LEADER_MIN_PRICE_HEADER);
        with_csv_delimiter(p_headers);
    }
    remove_last_character(p_headers);
}

//build_leader_csv_line assigns rows depending of the colums of user
static void build_leader_csv_line(Leader *p_leader, ExporterColumns *p_leader_columns, char *p_line) {
    char buffer[LINE_LIMIT];
    strcpy(p_line, "");
    with_break_line(p_line);
    if (p_leader_columns->specie) {
        sprintf(buffer, "%s%s", p_leader->specie, g_config.csv_delimiter);
        strcat(p_line, buffer);
    }

    if (p_leader_columns->variation) {
        sprintf(buffer, "%f%s", p_leader->variation, g_config.csv_delimiter);
        strcat(p_line, buffer);
    }

    if (p_leader_columns->purchase_price) {
        sprintf(buffer, "%f%s", p_leader->purchase_price), g_config.csv_delimiter;
        strcat(p_line, buffer);
    }

    if (p_leader_columns->sale_price) {
        sprintf(buffer, "%f%s", p_leader->sale_price, g_config.csv_delimiter);
        strcat(p_line, buffer);
    }

    if (p_leader_columns->opening_price) {
        sprintf(buffer, "%f%s", p_leader->opening_price, g_config.csv_delimiter);
        strcat(p_line, buffer);
    }

    if (p_leader_columns->max_price) {
        sprintf(buffer, "%f%s", p_leader->max_price, g_config.csv_delimiter);
        strcat(p_line, buffer);
    }

    if (p_leader_columns->min_price) {
        sprintf(buffer, "%f%s", p_leader->min_price, g_config.csv_delimiter);
        strcat(p_line, buffer);
    }
    remove_last_character(p_line);
}

//write_csv_file_with_data calls write headers and lines from leaders list
void write_csv_file_with_data(FILE *p_output, ParserOutput *p_data, ExporterColumns *p_columns) {
    exporter_debug_logger("Building and writing headers [event:write_csv_file_with_data]");
    char headers[LINE_LIMIT];
    build_leader_csv_headers(p_columns, headers);
    fprintf(p_output, "%s", headers);

    exporter_debug_logger("Building and writing lines [event:write_csv_file_with_data]");
    for (int i = 0; i < p_data->leaders_length; i++) {
        char line[LINE_LIMIT];
        build_leader_csv_line(p_data->leaders[i], p_columns, line);
        fprintf(p_output, "%s", line);
    }
}

ExportResult export_csv(const ParserOutput *p_data, const ExporterParams *p_params) {
    exporter_debug_logger("Starting export in CSV format [event:export_csv]");
    char output_path[PATH_LIMIT];
    output_path_with_extension(output_path, CSV_EXTENSION);
    exporter_debug_logger("Opening file in path %s [event:export_csv]", output_path);
    FILE *csv_file = fopen(output_path, "w");

    if (csv_file == NULL) {
        exporter_debug_logger("ERROR: Opening file in path %s [event:export_csv]", output_path);
        return EXPORT_RESULT_ERROR;
    }

    write_csv_file_with_data(csv_file, p_data, p_params->p_columns);
    fclose(csv_file);

    exporter_debug_logger("Export of CSV succesfully [event:export_csv]");
    return EXPORT_RESULT_OK;
}


