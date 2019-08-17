// EXPORT OPTIONS
#define EXPORT_CSV 1
#define EXPORT_XLSX 2

// PROCESS RESULT
#define RESULT_OK 0
#define RESULT_ERROR 1

typedef int ExportResult;
typedef char* Data;
typedef int Option;

ExportResult exportData(Option optionMethod, Data data);