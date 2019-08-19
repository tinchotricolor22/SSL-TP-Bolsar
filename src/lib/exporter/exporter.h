#include "exportertypes.h"
#include "../domain/leader.h"
#include "../logging/logging.h"
#include "stdio.h"

#define LINE_LIMIT 1000
#define PATH_LIMIT 100

#define HTML_EXTENSION ".html"
#define CSV_EXTENSION ".csv"

//LEADER
#define LEADER_SPECIE_HEADER "Especie"
#define LEADER_VARIATION_HEADER "Variación %"
#define LEADER_PURCHASE_PRICE_HEADER "Precio de compra"
#define LEADER_SALE_PRICE_HEADER "Precio de venta"
#define LEADER_OPENING_PRICE_HEADER "Apertura"
#define LEADER_MAX_PRICE_HEADER "Precio Máximo"
#define LEADER_MIN_PRICE_HEADER "Precio Mínimo"

ExporterColumns *
buildLeaderColumns(int specie, int variation, int purchasePrice, int salePrice, int openingPrice, int maxPrice,
                   int minPrice);

Logger exporterDebugLogger;

//initExporter injects dependency variables for exporter that includes logger functions
void initExporter(Logger debugLogger);

ExportResult exportLeadersCSV(Data *, ExporterParams *params);

ExportResult exportHTML(Data *, ExporterParams *params);

ExportResult exportLeadersStdout(Data *, ExporterParams *params);

//Common
void getOutPutPath(char *output, const char *extension);

void withDelimiter(char *str);

void withBreakLine(char *str);

void removeLastCharacter(char *str);

//LEADER CSV
void writeCSVFileWithData(FILE *output, Data *data, ExporterColumns *columns);

void buildLeaderCSVHeaders(ExporterColumns *leaderColumns, char *headers);

void buildLeaderCSVLine(Leader *leader, ExporterColumns *columns, char *line);

//LEADER HTML
void writeHTMLFileWithData(FILE *output, Data *data, ExporterColumns *columns, Formatter *formatter);

void writeHTMLTableWithData(FILE *output, Data *data, ExporterColumns *columns, Formatter *formatter);

void buildLeaderHTMLTableHeader(char *headers, ExporterColumns *leaderColumns);

void buildLeaderHTMLLine(Leader *leader, char *line, ExporterColumns *leaderColumns, Formatter *formatter);

void writePropertyAndValueInTableRowTagOpening(char *output, Format *format);

//HTML Tags File
void writeHTMLMainTagsOpening(FILE *output);

void writeHTMLMainTagsClosing(FILE *output);

void writeHTMLTableTagOpening(FILE *output);

void writeHTMLTableTagClosing(FILE *output);

void writeHTMLTableHeaderTagsOpening(FILE *output);

void writeHTMLTableHeaderTagsClosing(FILE *output);

void writeHTMLTableBodyTagsOpening(FILE *output);

void writeHTMLTableBodyTagsClosing(FILE *output);

void writeHTMLTableRowTagsOpening(FILE *output);

void writeHTMLTableRowTagsClosing(FILE *output);

void writeHTMLTableColumnTagsOpening(FILE *output);

void writeHTMLTableColumnTagsClosing(FILE *output);

//HTML Tags String
void writeStringHTMLMainTagsOpening(char *output);

void writeStringHTMLMainTagsClosing(char *output);

void writeStringHTMLTableTagOpening(char *output);

void writeStringHTMLTableTagClosing(char *output);

void writeStringHTMLTableHeaderTagsOpening(char *output);

void writeStringHTMLTableHeaderTagsClosing(char *output);

void writeStringHTMLTableBodyTagsOpening(char *output);

void writeStringHTMLTableBodyTagsClosing(char *output);

void writeStringHTMLTableRowTagsOpening(char *output);

void writeStringHTMLTableRowTagsOpeningAndApplyFormats(char *output, Format **format_list, int format_list_length);

void writeStringHTMLTableRowTagsClosing(char *output);

void writeStringHTMLTableColumnTagsOpening(char *output);

void writeStringHTMLTableColumnTagsClosing(char *output);