#ifndef EXPORTER_HEADER
#define EXPORTER_HEADER

#include "../domain/leader.h"
#include "../logging/logging.h"
#include "stdio.h"
#include "../parser/parser.h"
#include "../formatter/formatter.h"

// PROCESS RESULT
#define EXPORT_RESULT_OK 0
#define EXPORT_RESULT_ERROR 1

#define HTML_EXTENSION ".html"
#define CSV_EXTENSION ".csv"

#define LINE_LIMIT 1000
#define PATH_LIMIT 100

/**********LEADER**********/

#define LEADER_SPECIE_HEADER "Especie"
#define LEADER_VARIATION_HEADER "Variación %"
#define LEADER_PURCHASE_PRICE_HEADER "Precio de compra"
#define LEADER_SALE_PRICE_HEADER "Precio de venta"
#define LEADER_OPENING_PRICE_HEADER "Apertura"
#define LEADER_MAX_PRICE_HEADER "Precio Máximo"
#define LEADER_MIN_PRICE_HEADER "Precio Mínimo"

//LeaderColumns represents structs with leaders p_columns
typedef struct LeaderColumns {
    int specie;
    int variation;
    int purchase_price;
    int sale_price;
    int opening_price;
    int max_price;
    int min_price;
} LeaderColumns;

//build_leader_columns instanciate ExportColumns struct with leaders columns args
LeaderColumns *build_leader_columns(const int, const int, const int, const int, const int, const int, const int);

/**************************/

//data_debug_logger is logger for exporter
Logger exporter_debug_logger;

//init_exporter injects dependency variables for exporter that includes logger functions
void init_exporter(const Logger);

//output_path_with_extension appends extension to output_path from config
void output_path_with_extension(char *output, const char *extension);

//ExporterColumns represents structs columns
typedef LeaderColumns ExporterColumns;

//ExporterParams represents structs with columns and formatter config
typedef struct ExporterParams {
    ExporterColumns *p_columns;
    FormatCondition **formats_conditions_list;
    int formats_conditions_list_length;
} ExporterParams;

//ExportResult represents the result of export methods
typedef int ExportResult;

//ExporterMethod represents the export methods
typedef ExportResult(*ExporterMethod)(const ParserOutput *, const ExporterParams *);

//write_csv_file_with_data calls write headers and lines from leaders list
void write_csv_file_with_data(FILE *, ParserOutput *, ExporterColumns *);

//export_csv exports  CSV file from input on output_path_config
ExportResult export_csv(const ParserOutput *p_data, const ExporterParams *p_params);

//export_html exports HTML file from input on output_path_config
ExportResult export_html(const ParserOutput *, const ExporterParams *);

//export_stdout prints in screen (stdout)
ExportResult export_stdout(const ParserOutput *, const ExporterParams *);

#endif