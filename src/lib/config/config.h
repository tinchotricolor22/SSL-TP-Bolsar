#ifndef CONFIG_HEADER
#define CONFIG_HEADER

#if defined(_WIN32) || defined(_WIN64)
const char* os = "Windoze";
#define ONLINE_CMD ".\\GnuWin32\\bin\\wget -q --user-agent=\"Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.103 Safari/537.36\" -O - http://52.67.191.9/SSL/lideres-bcba_limpio.html"
#else
#if defined(__linux)
const char* os = "Linux";
#define ONLINE_CMD "wget -q -O - http://52.67.191.9/SSL/lideres-bcba_limpio.html"
#else
#if defined(__APPLE__) || defined(__MACH__)
#define OS "MAC"
#define ONLINE_CMD "wget -q -O - http://52.67.191.9/SSL/lideres-bcba_limpio.html"

#endif
#endif
#endif
#include "../logging/logging.h"

Logger configDebugLogger;

void initConfig(Logger debugLogger);

//getUserOS returns user's Operating System 
char *getUserOS();

//getDataFSPath returns file system path
char *getDataFSPath();

//getParserURL returns URL to connect the parser
char *getParserURL();

char *getAuxTableFileName();

char *getExporterOutputPath();

char *getCSVDelimiter();

#endif