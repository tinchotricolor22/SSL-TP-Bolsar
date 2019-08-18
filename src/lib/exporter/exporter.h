#include "../extractor/extractor.h"
// PROCESS RESULT
#define EXPORT_OK 0
#define EXPORT_ERROR 1

#define LINE_LIMIT 1000
#define PATH_LIMIT 100

//LEADER
#define LEADER_SPECIE_HEADER "Especie"
#define LEADER_VARIATION_HEADER "Variación %"
#define LEADER_PURCHASE_PRICE_HEADER "Precio de compra"
#define LEADER_SALE_PRICE_HEADER "Precio de venta"
#define LEADER_OPENING_PRICE_HEADER "Apertura"
#define LEADER_MAX_PRICE_HEADER "Precio Máximo"
#define LEADER_MIN_PRICE_HEADER "Precio Mínimo"

typedef struct LeaderColumns{
    int specie;
    int variation;
    int purchasePrice;
    int salePrice;
    int openingPrice;
    int maxPrice;
    int minPrice;
} LeaderColumns;

typedef LeaderColumns ColumnsExporterOptions;
Logger exporterDebugLogger;

typedef int ExportResult;
typedef ExportResult(*ExporterMethod)(Data*,ColumnsExporterOptions*);

//initExporter injects dependency variables for exporter that includes logger functions
void initExporter(Logger debugLogger);

ExportResult exportLeadersCSV(Data*,ColumnsExporterOptions *columnsOptions);
ExportResult exportHTML(Data*,ColumnsExporterOptions *columnsOptions);
ExportResult exportLeadersStdout(Data*,ColumnsExporterOptions *columnsOptions);

//LEADER
ColumnsExporterOptions* buildLeaderColumns(int specie, int variation, int purchasePrice, int salePrice, int openingPrice, int maxPrice, int minPrice);
void buildLeaderCSVHeaders(ColumnsExporterOptions *leaderColumns, char* headers);
void writeCSVFileWithData(FILE* output, Data* data, ColumnsExporterOptions *columns);
void buildLeaderCSVLine(Leader *leader, ColumnsExporterOptions *columns,char *line);

void getOutPutPath(char* output);
void withDelimiter(char* str);
void withBreakLine(char* str);
void removeLastCharacter(char* str);