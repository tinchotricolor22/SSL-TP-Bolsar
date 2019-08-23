#include "config.h"
#include "stdio.h"
#include "string.h"

void init_config(const Logger debug_logger) {
    config_debug_logger = debug_logger;
}

ResultConfig init_config_properties() {
    config_debug_logger("Opening file in filesystem resources/config.properties file [event:init_config_properties]");

    FILE *config_properties = fopen("resources/config.properties", "r");

    if (config_properties == NULL) {
        init_config_properties( "ERROR: Opening file in path resources/config.properties [event:init_config_properties]");
        return RESULT_CONFIG_ERROR;
    }

    char id[50], value[50];
    while (fscanf(config_properties, "%[^=]=%s", &id, &value) != EOF) {
        if (strstr(id, "fs_data_path")) {
            strcpy(g_config.fs_data_path, value);
        } else if (strstr(id, "online_data_url")) {
            strcpy(g_config.wget_cmd, WGET_CMD);
            strcat(g_config.wget_cmd, value);
        } else if (strstr(id, "exporter_output_path")) {
            strcpy(g_config.exporter_output_path, value);
        } else if (strstr(id, "csv_delimiter")) {
            strcpy(g_config.csv_delimiter, value);
        }
    }
    fclose(config_properties);
    return RESULT_CONFIG_OK;
}