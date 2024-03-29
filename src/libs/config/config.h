#ifndef CONFIG_HEADER
#define CONFIG_HEADER

#if defined(_WIN32) || defined(_WIN64)
#define USER_OS "WINDOWS"
#define WGET_CMD "commands\\GnuWin32\\bin\\wget -qO - "
#else
#if defined(__linux)
#define USER_OS "LINUX"
#define WGET_CMD "commands/wget -q -O - "
#else
#if defined(__APPLE__) || defined(__MACH__)
#define USER_OS "MAC"
#define WGET_CMD "commands/wget -q -O - "

#endif
#endif
#endif
#include "../logging/logging.h"

#define RESULT_CONFIG_OK 0
#define RESULT_CONFIG_ERROR 1

//ResultConfig represents the result of init_config
typedef int ResultConfig;

//Config contains all config parameters
static struct Config {
    char fs_data_path[100];
    char wget_cmd[100];
    char exporter_output_path[100];
    char csv_delimiter[100];
};

//g_config represents config to be used in all the lifecycle of the program
struct Config g_config;

//config_debug_logger is logger for config
Logger config_debug_logger;

//init_config inits config_debug_logger
void init_config(const Logger);

//init_config inits g_config variable extracting data from config.properties file
ResultConfig init_config_properties();

#endif