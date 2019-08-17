#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "extractor.h"

#define SUFFIX_SPECIE "3_SIMB"

struct Leader *leaders[100];
int leaders_length = 0;

void initExtractorGlobalVariables(char* userOS, char* url, char* fsPath, int(*stdLogger)(const char*,...),int(*debugLogger)(const char*,...)){
    UserOS = userOS;
    FSPath = fsPath;
    URL = url;
    extractorLogger = stdLogger;
    extractorDebugLogger = debugLogger;
}

Data extractData(Option optionMethod){
    switch (optionMethod)
    {
        case METHOD_ONLINE:
            return extractDataWithOnlineMethod();
        break;

        default:
            return extractDataWithFSMethod();
        break;
    }
}

Data extractDataWithOnlineMethod(){
    extractorDebugLogger("Starting to extract data with online method [event:extractDataWithOnlineMethod]");
    return "asd";
}

Data extractDataWithFSMethod(){
    extractorDebugLogger("Starting to extract data with filesystem method [event:extractDataWithFSMethod]");
    FILE *file;

    extractorDebugLogger("Opening file in filesystem path: %s [event:extractDataWithFSMethod]",FSPath);
    file = fopen(FSPath,"r");

    if (file == NULL){
        extractorLogger("ERROR: Cannot open file in path: %s [event:extractDataWithFSMethod]",FSPath);
    }

    Data data = extractHTMLFromTableID("tbAcciones",file);

    fclose(file);
    return data;
}

Data extractHTMLFromTableID(char* ID, FILE *htmlFile){
    extractorDebugLogger("Starting to search tableID in htmlFile [event:extractHTMLFromTableID]");
    char table[40000], tableID[50];
    char* tableIDAux = "id=";
    strcat(tableID,tableIDAux);
    strcat(tableID,"\"");
    strcat(tableID,ID);
    strcat(tableID,"\"");

    extractorDebugLogger("searching %s",tableID);
    while(!feof(htmlFile)){
        fgets(table,40000,htmlFile);
        if(strstr(table,tableID)){
            extractorDebugLogger("founded");
            break;
        }
    }

    FILE* tableFile;
    tableFile = createAuxFileFromTable(table);
    char rows[400][400];
    extractRowsFromTable(tableFile,rows);
    fillLeadersFromRows(rows);
    fclose(tableFile);

    return "especies";
}

Data extractRowsFromTable(FILE* tableFile, char rows[400][400]){
    extractorDebugLogger("Starting to search especies in table with conditionRowName [event:extractRowsFromTable]");
    //"<td id="CRES_3_VAR"
    int countRows = 0;
    char match[200],aux[400];

    //volvemos al principio del file
    rewind(tableFile);
    while(fscanf(tableFile,"%s[^'</td><td']",match) != EOF){
        printf("match de row: %s",match);
        strcpy(aux,"");
        strcpy(aux,match);
        
        while(!strstr(match,"</td><td") && fscanf(tableFile,"%s[^'</td><td']",match) != EOF){
            strcat(aux,match);
        }
        strcpy(rows[countRows],aux);
        countRows++;
    }
    
    return ";";
}

FILE* createAuxFileFromTable(char* table){
    FILE* tableFile = fopen("resources/aux_table_file.txt", "w+");
    
    if(tableFile == NULL){
        extractorLogger("ERROR: Cannot open file in path: %s [event:extractDataWithFSMethod]",FSPath);
        return tableFile;
    }

    fprintf(tableFile,"%s",table);
    return tableFile;
}

void fillLeadersFromRows(char rows[400][400]){
    extractorDebugLogger("Starting to fill leaders [event:fillLeadersFromRows]");
    struct Leader *actualProcessingLeader;

    for(int countRows=0, retCount = 0; countRows < 400; countRows++){
        char propertyID[10],prefix[50],suffix[50];
        sscanf(rows[countRows],"%[^\"]\"%[^_]_%[^\"]",propertyID,prefix,suffix);
        printf("suffix: %s",suffix);
        if(!strcmp(suffix,SUFFIX_SPECIE)){
            printf("matchea");
            struct Leader *newLeader = new_leader();
            char* specie = "specie_test";//extractStringValue(rows[countRows]);

            strcpy(newLeader->id, prefix);
            strcpy(newLeader->specie, specie);
            add_leader(newLeader);
            actualProcessingLeader = newLeader;
        }
    }
}

Data extractValuesFromRowsID(char rows[400][400],char *id_suffix){
    extractorDebugLogger("Starting to extract values from row ID [event:extractRowsFromTable]");
    void* ret[400];

    for(int countRows=0, retCount = 0; countRows < 400; countRows++){
        char identifier[10],prefix[50],suffix[50];

        sscanf(rows[countRows],"%[^\"]\"%[^_]_%[^\"]",identifier,prefix,suffix);
        if(strstr(suffix,id_suffix)){
            char rest[100];
            char stringDouble[10];
            //TODO: acá habría que mandar una function generic
            sscanf(rows[countRows],"%[^>]>%[^&]",rest,stringDouble);

            trim(stringDouble,stringDouble);
            replace(stringDouble,',','.');

            double result = atof(stringDouble);
            printf("resultado: %f   \n",result);
        }
    }
    return "";
}

void trim(const char *input, char *result)
{
  int i, j = 0;
  for (i = 0; input[i] != '\0'; i++) {
    if (!isspace((unsigned char) input[i])) {
      result[j++] = input[i];
    }
  }
  result[j] = '\0';
}

void replace(char *input, const char character, const char replace)
{   
  for (int i = 0; input[i] != '\0'; i++) {
    if (input[i] == character){
        input[i] = replace;
    }
  }
}

struct Leader* findLeaderByID(const char* id){
    for(int i = 0; i< 100;i++){
        if (strcmp(leaders[i]->id, id)){
            return leaders[i];
        }
    }
    return NULL;
}

struct Leader* new_leader(){
    struct Leader* leader ={"",
            "",
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0};
    return  leader;
}

void add_leader(struct Leader *leader){
    if (leaders_length < 100){
        leaders[leaders_length++] = leader;
    }
}

/*
void closeFiles(){

}

void removeAuxFiles(){

}*/