#ifndef EXPORTER_HEADER
#define EXPORTER_HEADER

#include "exporter.h"
#include "../config/config.h"
#include "../logging/logging.h"
#include "string.h"
#include "stdio.h"

void initExporter(Logger debugLogger){
    exporterDebugLogger = debugLogger;
}

ExporterColumns* buildLeaderColumns(int specie, int variation, int purchasePrice, int salePrice, int openingPrice, int maxPrice, int minPrice){
    LeaderColumns *leaderColumns = malloc(sizeof (*leaderColumns));
    leaderColumns->specie = specie;
    leaderColumns->variation = variation;
    leaderColumns->purchasePrice = purchasePrice;
    leaderColumns->salePrice = salePrice;
    leaderColumns->openingPrice = openingPrice;
    leaderColumns->maxPrice = maxPrice;
    leaderColumns->minPrice = minPrice;
    return leaderColumns;
}

void getOutPutPath(char* output,const char* extension){
    strcpy(output,getExporterOutputPath());
    strcat(output,extension);
}

void withDelimiter(char* str){
    strcat(str,getCSVDelimiter());
}

void withBreakLine(char* str){
    strcat(str,"\n");
}

void removeLastCharacter(char* str){
    int length = strlen(str);
    if(length > 0){
        str[length-1] = '\0';
    }
}

#endif