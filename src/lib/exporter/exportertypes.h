#ifndef EXPORTER_TYPES_HEADER
#define EXPORTER_TYPES_HEADER

#include "../parser/parsertypes.h" // Por el momento
#include "../formatter/formattertypes.h"

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
    Formatter *formatter;
} ExporterParams;

typedef int ExportResult;

typedef ExportResult(*ExporterMethod)(Data *, ExporterParams *);

#endif