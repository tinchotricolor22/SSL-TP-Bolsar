#include "config.h"
#include "stdio.h"
#include "string.h"

int init_config() {
    FILE *config_properties = fopen("resources/config.properties", "r");

    if (config_properties == NULL) {
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