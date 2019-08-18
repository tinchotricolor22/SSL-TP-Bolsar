// PROCESS RESULT
#define EXPORT_OK 0
#define EXPORT_ERROR 1

typedef int ExportResult;
typedef ExportResult(*ExporterMethod)(Data*);

ExportResult exportCSV(Data*);
ExportResult exportHTML(Data*);