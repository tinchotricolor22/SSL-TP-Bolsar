#ifndef CONFIG_HEADER
#define CONFIG_HEADER

#include "../logging/logging.h"

Logger configDebugLogger;

void initConfig(Logger debugLogger);

//getUserOS returns user's Operating System 
char *getUserOS();

//getExtractorFSPath returns file system path
char *getExtractorFSPath();

//getExtractorURL returns URL to connect the extractor
char *getExtractorURL();

char *getAuxTableFileName();

char *getExporterOutputPath();

char *getCSVDelimiter();

#endif