#ifndef CONFIG_HEADER
#define CONFIG_HEADER

#include "../logging/logging.h"

Logger configDebugLogger;

void initConfig(Logger debugLogger);

//getUserOS returns user's Operating System 
char *getUserOS();

//getParserFSPath returns file system path
char *getParserFSPath();

//getParserURL returns URL to connect the parser
char *getParserURL();

char *getAuxTableFileName();

char *getExporterOutputPath();

char *getCSVDelimiter();

#endif