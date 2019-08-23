#include "preferences.h"
#include "stdlib.h"
#include "../utils/commons.h"
#include "../exporter/exporter.h"

ProcessParams *default_leaders_05_variation_screen() {
    ProcessParams *process_params = malloc(sizeof *process_params);

    process_params->data_method = _get_data_with_online_method;
    process_params->parser_method = parseDataFromHTML;
    process_params->exporter_method = exportStdout;
    process_params->p_columns = buildLeaderColumns(1, 0, 0, 0, 0, 0, 0);
    process_params->filters_list = malloc(sizeof process_params->filters_list[0] * FILTERS_MAX_LENGTH);
    process_params->filters_list_length = 0;
    add(process_params->filters_list, _leader_filter_major_05_variation, &process_params->filters_list_length, FILTERS_MAX_LENGTH);

    process_params->formats_conditions_list_length = 0;

    return process_params;
}

ProcessParams *default_leaders_05_variation_HTML() {
    ProcessParams *process_params = malloc(sizeof *process_params);

    process_params->data_method = _get_data_with_online_method;
    process_params->parser_method = parseDataFromHTML;
    process_params->exporter_method = exportHTML;
    process_params->p_columns = buildLeaderColumns(1, 0, 0, 0, 0, 0, 0);

    process_params->filters_list = malloc(sizeof process_params->filters_list[0] * FILTERS_MAX_LENGTH);
    process_params->filters_list_length = 0;
    add(process_params->filters_list, _leader_filter_major_05_variation, &process_params->filters_list_length, FILTERS_MAX_LENGTH);

    process_params->formats_conditions_list = malloc(sizeof process_params->formats_conditions_list[0] * MAX_FORMATS);
    process_params->formats_conditions_list_length = 0;
    add(process_params->formats_conditions_list, _leader_purchase_sale_major_opening,
        &process_params->formats_conditions_list_length, MAX_FORMATS);

    return process_params;
}

ProcessParams *default_leaders_sale_purchase_CSV() {
    ProcessParams *process_params = malloc(sizeof *process_params);

    process_params->data_method = _get_data_with_online_method;
    process_params->parser_method = parseDataFromHTML;
    process_params->exporter_method = exportCSV;
    process_params->p_columns = buildLeaderColumns(1, 1, 1, 1, 1, 1, 1);
    process_params->filters_list_length = 0;
    process_params->formats_conditions_list_length = 0;

    return process_params;
}

ProcessParams *default_preferences() {
    ProcessParams *process_params = malloc(sizeof *process_params);

    process_params->data_method = _get_data_with_fs_method;
    process_params->parser_method = parseDataFromHTML;
    process_params->exporter_method = exportCSV;
    process_params->p_columns = buildLeaderColumns(1, 1, 1, 1, 1, 1, 1);
    process_params->filters_list_length = 0;
    process_params->formats_conditions_list_length = 0;

    return process_params;
}
