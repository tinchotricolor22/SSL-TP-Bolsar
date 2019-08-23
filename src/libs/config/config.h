#ifndef CONFIG_HEADER
#define CONFIG_HEADER

#if defined(_WIN32) || defined(_WIN64)
#define USER_OS "WINDOWS"
#define WGET_CMD ".\\GnuWin32\\bin\\wget -q --user-agent=\"Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.103 Safari/537.36\" -O - "
#else
#if defined(__linux)
#define USER_OS "LINUX"
#define WGET_CMD "wget -q -O - "
#else
#if defined(__APPLE__) || defined(__MACH__)
#define USER_OS "MAC"
#define WGET_CMD "wget -q -O - "

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
    char aux_table_file_name[100]; //TODO:Eliminar luego del parser
};

//g_config represents config to be used in all the lifecycle of the program
struct Config g_config;

//init_config inits g_config variable extracting data from config.properties file
ResultConfig init_config();

#endif