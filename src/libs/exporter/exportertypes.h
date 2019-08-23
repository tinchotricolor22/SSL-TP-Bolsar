#ifndef EXPORTER_TYPES_HEADER
#define EXPORTER_TYPES_HEADER

#include "../parser/parser.h"
#include "../formatter/formatter.h"

// PROCESS RESULT
#define EXPORT_RESULT_OK 0
#define EXPORT_RESULT_ERROR 1

typedef struct LeaderColumns {
    int specie;
    int variation;
    int purchasePrice;
    int salePrice;
    int openingPrice;
    int maxPrice;
    int minPrice;
} LeaderColumns;

typedef LeaderColumns ExporterColumns;

typedef struct ExporterParams {
    ExporterColumns *columns;
    FormatCondition **formats_conditions;
    int formats_conditions_length;
} ExporterParams;

typedef int ExportResult;

typedef ExportResult(*ExporterMethod)(ParserOutput *, ExporterParams *);

#endif