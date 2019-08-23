#include "exporter.h"
#include "../config/config.h"
#include "../logging/logging.h"
#include "string.h"
#include "stdio.h"

ExportResult exportCSV(ParserOutput *data, ExporterParams *params) {
    exporterDebugLogger("Starting export in CSV format [event:exportCSV]");
    char outputPath[PATH_LIMIT];
    getOutPutPath(outputPath, CSV_EXTENSION);
    exporterDebugLogger("Opening file in path %s [event:exportCSV]", outputPath);
    FILE *csvFile = fopen(outputPath, "w");

    if (csvFile == NULL) {
        exporterDebugLogger("ERROR: Opening file in path %s [event:exportCSV]", outputPath);
        return EXPORT_RESULT_ERROR;
    }

    writeCSVFileWithData(csvFile, data, params->columns);
    fclose(csvFile);

    exporterDebugLogger("Export of CSV succesfully [event:exportCSV]");
    return EXPORT_RESULT_OK;
}

void writeCSVFileWithData(FILE *output, ParserOutput *data, ExporterColumns *columns) {
    exporterDebugLogger("Building and writing headers [event:writeCSVFileWithData]");
    char headers[LINE_LIMIT];
    buildLeaderCSVHeaders(columns, headers);
    fprintf(output, "%s", headers);

    exporterDebugLogger("Building and writing lines [event:writeCSVFileWithData]");
    for (int i = 0; i < data->leaders_length; i++) {
        char line[LINE_LIMIT];
        buildLeaderCSVLine(data->leaders[i], columns, line);
        fprintf(output, "%s", line);
    }
}

void buildLeaderCSVHeaders(ExporterColumns *leaderColumns, char *headers) {
    strcpy(headers, "");
    if (leaderColumns->specie) {
        strcat(headers, LEADER_SPECIE_HEADER);
        withDelimiter(headers);
    }

    if (leaderColumns->variation) {
        strcat(headers, LEADER_VARIATION_HEADER);
        withDelimiter(headers);
    }

    if (leaderColumns->purchasePrice) {
        strcat(headers, LEADER_PURCHASE_PRICE_HEADER);
        withDelimiter(headers);
    }

    if (leaderColumns->salePrice) {
        strcat(headers, LEADER_SALE_PRICE_HEADER);
        withDelimiter(headers);
    }

    if (leaderColumns->openingPrice) {
        strcat(headers, LEADER_OPENING_PRICE_HEADER);
        withDelimiter(headers);
    }

    if (leaderColumns->maxPrice) {
        strcat(headers, LEADER_MAX_PRICE_HEADER);
        withDelimiter(headers);
    }

    if (leaderColumns->minPrice) {
        strcat(headers, LEADER_MIN_PRICE_HEADER);
        withDelimiter(headers);
    }
    removeLastCharacter(headers);
}

void buildLeaderCSVLine(Leader *leader, ExporterColumns *leaderColumns, char *line) {
    char buffer[LINE_LIMIT];
    strcpy(line, "");
    withBreakLine(line);
    if (leaderColumns->specie) {
        sprintf(buffer, "%s,", leader->specie);
        strcat(line, buffer);
    }

    if (leaderColumns->variation) {
        sprintf(buffer, "%f,", leader->variation);
        strcat(line, buffer);
    }

    if (leaderColumns->purchasePrice) {
        sprintf(buffer, "%f,", leader->purchase_price);
        strcat(line, buffer);
    }

    if (leaderColumns->salePrice) {
        sprintf(buffer, "%f,", leader->sale_price);
        strcat(line, buffer);
    }

    if (leaderColumns->openingPrice) {
        sprintf(buffer, "%f,", leader->opening_price);
        strcat(line, buffer);
    }

    if (leaderColumns->maxPrice) {
        sprintf(buffer, "%f,", leader->max_price);
        strcat(line, buffer);
    }

    if (leaderColumns->minPrice) {
        sprintf(buffer, "%f,", leader->min_price);
        strcat(line, buffer);
    }
    removeLastCharacter(line);
}