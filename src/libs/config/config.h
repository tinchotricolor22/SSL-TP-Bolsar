#ifndef CONFIG_HEADER
#define CONFIG_HEADER

#if defined(_WIN32) || defined(_WIN64)
#define OS "WINDOWS"
#define ONLINE_CMD ".\\GnuWin32\\bin\\wget -q --user-agent=\"Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.103 Safari/537.36\" -O - http://52.67.191.9/SSL/lideres-bcba.html"
#else
#if defined(__linux)
#define OS "LINUX"
#define ONLINE_CMD "wget -q -O - http://52.67.191.9/SSL/lideres-bcba.html"
#else
#if defined(__APPLE__) || defined(__MACH__)
#define OS "MAC"
#define ONLINE_CMD "wget -q -O - http://52.67.191.9/SSL/lideres-bcba.html"

#endif
#endif
#endif
#include "../logging/logging.h"

Logger configDebugLogger;

void initConfig(Logger debugLogger);

//getDataFSPath returns file system path
char *getDataFSPath();

//getParserCMD returns the command to get data from server
char *getParserCMD();

char *getAuxTableFileName();

char *getExporterOutputPath();

char *getCSVDelimiter();

#endif