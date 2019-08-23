#include "exporter.h"
#include "string.h"
#include "../utils/html_writer.h"
#include "../formatter/formatter.h"

static void write_property_and_value_in_table_row_tag_ppening(char *p_output, Format *p_format) {
    if (p_format->apply_component ==
        COMPONENT_TR) { //Iterar esto para solo filtrar los que son TR en la función anterior
        char buffer[50];
        sprintf(buffer, "<tr %s=\"%s\">", p_format->identifier, p_format->value);
        strcat(p_output, buffer);
    }
}

static void write_string_html_table_row_tags_opening_and_apply_formats(Leader *p_leader, char *p_output,
                                                                       Format **formats_conditions_list,
                                                                       int formats_conditions_list_length) {
    for (int i = 0; i < formats_conditions_list_length; i++) {
        FormatCondition format_condition = formats_conditions_list[i];
        Format *format = format_condition(p_leader);

        if (format != NULL) {
            write_property_and_value_in_table_row_tag_ppening(p_output, format);
        }
    }
}

void
build_leader_html_line(Leader *p_leader, char *p_line, ExporterColumns *p_leader_columns, Format **formats_list,
                       int formats_list_length) {
    char buffer[LINE_LIMIT];
    strcpy(p_line, "");

    write_string_html_table_row_tags_opening_and_apply_formats(p_leader, p_line, formats_list, formats_list_length);

    if (p_leader_columns->specie) {
        write_string_html_table_column_tags_opening(p_line);
        sprintf(buffer, "%s", p_leader->specie);
        strcat(p_line, buffer);
        write_string_html_table_column_tags_closing(p_line);
    }

    if (p_leader_columns->variation) {
        write_string_html_table_column_tags_opening(p_line);
        sprintf(buffer, "%f", p_leader->variation);
        strcat(p_line, buffer);
        write_string_html_table_column_tags_closing(p_line);
    }

    if (p_leader_columns->purchase_price) {
        write_string_html_table_column_tags_opening(p_line);
        sprintf(buffer, "%f", p_leader->purchase_price);
        strcat(p_line, buffer);
        write_string_html_table_column_tags_closing(p_line);
    }

    if (p_leader_columns->sale_price) {
        write_string_html_table_column_tags_opening(p_line);
        sprintf(buffer, "%f", p_leader->sale_price);
        strcat(p_line, buffer);
        write_string_html_table_column_tags_closing(p_line);
    }

    if (p_leader_columns->opening_price) {
        write_string_html_table_column_tags_opening(p_line);
        sprintf(buffer, "%f", p_leader->opening_price);
        strcat(p_line, buffer);
        write_string_html_table_column_tags_closing(p_line);
    }

    if (p_leader_columns->max_price) {
        write_string_html_table_column_tags_opening(p_line);
        sprintf(buffer, "%f", p_leader->max_price);
        strcat(p_line, buffer);
        write_string_html_table_column_tags_closing(p_line);
    }

    if (p_leader_columns->min_price) {
        write_string_html_table_column_tags_opening(p_line);
        sprintf(buffer, "%f", p_leader->min_price);
        strcat(p_line, buffer);
        write_string_html_table_column_tags_closing(p_line);
    }
    write_string_html_table_row_tags_closing(p_line);
}


static void build_leader_html_table_header(char *p_headers, ExporterColumns *p_leader_columns) {
    strcpy(p_headers, "");

    write_string_html_table_header_tags_opening(p_headers);
    write_string_html_table_row_tags_opening(p_headers);

    if (p_leader_columns->specie) {
        write_string_html_table_column_tags_opening(p_headers);
        strcat(p_headers, LEADER_SPECIE_HEADER);
        write_string_html_table_column_tags_closing(p_headers);
    }

    if (p_leader_columns->variation) {
        write_string_html_table_column_tags_opening(p_headers);
        strcat(p_headers, LEADER_VARIATION_HEADER);
        write_string_html_table_column_tags_closing(p_headers);
    }

    if (p_leader_columns->purchase_price) {
        write_string_html_table_column_tags_opening(p_headers);
        strcat(p_headers, LEADER_PURCHASE_PRICE_HEADER);
        write_string_html_table_column_tags_closing(p_headers);
    }

    if (p_leader_columns->sale_price) {
        write_string_html_table_column_tags_opening(p_headers);
        strcat(p_headers, LEADER_SALE_PRICE_HEADER);
        write_string_html_table_column_tags_closing(p_headers);
    }

    if (p_leader_columns->opening_price) {
        write_string_html_table_column_tags_opening(p_headers);
        strcat(p_headers, LEADER_OPENING_PRICE_HEADER);
        write_string_html_table_column_tags_closing(p_headers);
    }

    if (p_leader_columns->max_price) {
        write_string_html_table_column_tags_opening(p_headers);
        strcat(p_headers, LEADER_MAX_PRICE_HEADER);
        write_string_html_table_column_tags_closing(p_headers);
    }

    if (p_leader_columns->min_price) {
        write_string_html_table_column_tags_opening(p_headers);
        strcat(p_headers, LEADER_MIN_PRICE_HEADER);
        write_string_html_table_column_tags_closing(p_headers);
    }
    write_string_html_table_row_tags_closing(p_headers);
    write_string_html_table_header_tags_closing(p_headers);
}

static void
write_html_table_with_data(FILE *p_output, ParserOutput *p_data, ExporterColumns *p_columns, Format **formats_list,
                           int formats_list_length) {
    exporter_debug_logger("Building and writing Table [event:write_html_table_with_data]");

    write_html_table_tag_opening(p_output);

    exporter_debug_logger("Building and writing headers [event:write_html_table_with_data]");

    char headers[LINE_LIMIT];
    build_leader_html_table_header(headers, p_columns);
    fprintf(p_output, "%s", headers);

    exporter_debug_logger("Building and writing lines [event:write_html_table_with_data]");

    write_html_table_body_tags_opening(p_output);
    write_html_table_body_tags_opening(p_output);
    for (int i = 0; i < p_data->leaders_length; i++) {
        char line[LINE_LIMIT];
        build_leader_html_line(p_data->leaders[i], line, p_columns, formats_list, formats_list_length);
        fprintf(p_output, "%s", line);
    }
    write_html_table_body_tags_closing(p_output);
    write_html_table_body_tags_closing(p_output);
}

static void
write_html_file_with_data(FILE *p_output, ParserOutput *p_data, ExporterColumns *p_columns, Format **formats_list,
                          int formats_list_length) {
    write_html_main_tags_opening(p_output);
    write_html_table_with_data(p_output, p_data, p_columns, formats_list, formats_list_length);
    write_html_main_tags_closing(p_output);
}

ExportResult export_html(const ParserOutput *p_data, const ExporterParams *p_params) {
    exporter_debug_logger("Starting export in HTML format [event:export_html]");
    char output_path[PATH_LIMIT];
    output_path_with_extension(output_path, HTML_EXTENSION);
    exporter_debug_logger("Opening file in path %s [event:export_html]", output_path);
    FILE *html_file = fopen(output_path, "w");

    if (html_file == NULL) {
        exporter_debug_logger("ERROR: Opening file in path %s [event:export_html]", output_path);
        return EXPORT_RESULT_ERROR;
    }

    write_html_file_with_data(html_file, p_data, p_params->p_columns, p_params->formats_conditions_list,
                              p_params->formats_conditions_list_length);
    fclose(html_file);

    exporter_debug_logger("Export of HTML succesfully [event:export_html]");
    return EXPORT_RESULT_OK;
}
