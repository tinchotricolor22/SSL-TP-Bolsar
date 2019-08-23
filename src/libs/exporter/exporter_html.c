#include "exporter.h"
#include "string.h"
#include "../formatter/formatter.h"
#include "../utils/commons.h"

ExportResult exportHTML(ParserOutput *data, ExporterParams *params) {
    exporterDebugLogger("Starting export in HTML format [event:exportHTML]");
    char outputPath[PATH_LIMIT];
    getOutPutPath(outputPath, HTML_EXTENSION);
    exporterDebugLogger("Opening file in path %s [event:exportHTML]", outputPath);
    FILE *htmlFile = fopen(outputPath, "w");

    if (htmlFile == NULL) {
        exporterDebugLogger("ERROR: Opening file in path %s [event:exportHTML]", outputPath);
        return EXPORT_RESULT_ERROR;
    }

    writeHTMLFileWithData(htmlFile, data, params->columns, params->formats_conditions, params->formats_conditions_length);
    fclose(htmlFile);

    exporterDebugLogger("Export of HTML succesfully [event:exportHTML]");
    return EXPORT_RESULT_OK;
}

void writeHTMLFileWithData(FILE *output, ParserOutput *data, ExporterColumns *columns, Format **formats,
                           int formats_length) {
    writeHTMLMainTagsOpening(output);
    writeHTMLTableWithData(output, data, columns, formats, formats_length);
    writeHTMLMainTagsClosing(output);
}

void writeHTMLTableWithData(FILE *output, ParserOutput *data, ExporterColumns *columns, Format **formats,
                            int formats_length) {
    exporterDebugLogger("Building and writing Table [event:writeHTMLTableWithData]");

    writeHTMLTableTagOpening(output);

    exporterDebugLogger("Building and writing headers [event:writeHTMLTableWithData]");

    char headers[LINE_LIMIT];
    buildLeaderHTMLTableHeader(headers, columns);
    fprintf(output, "%s", headers);

    exporterDebugLogger("Building and writing lines [event:writeHTMLTableWithData]");

    writeHTMLTableBodyTagsOpening(output);
    for (int i = 0; i < data->leaders_length; i++) {
        char line[LINE_LIMIT];
        buildLeaderHTMLLine(data->leaders[i], line, columns, formats, formats_length);
        fprintf(output, "%s", line);
    }
    writeHTMLTableBodyTagsClosing(output);
    writeHTMLTableTagClosing(output);
}

void buildLeaderHTMLTableHeader(char *headers, ExporterColumns *leaderColumns) {
    strcpy(headers, "");

    writeStringHTMLTableHeaderTagsOpening(headers);
    writeStringHTMLTableRowTagsOpening(headers);

    if (leaderColumns->specie) {
        writeStringHTMLTableColumnTagsOpening(headers);
        strcat(headers, LEADER_SPECIE_HEADER);
        writeStringHTMLTableColumnTagsClosing(headers);
    }

    if (leaderColumns->variation) {
        writeStringHTMLTableColumnTagsOpening(headers);
        strcat(headers, LEADER_VARIATION_HEADER);
        writeStringHTMLTableColumnTagsClosing(headers);
    }

    if (leaderColumns->purchasePrice) {
        writeStringHTMLTableColumnTagsOpening(headers);
        strcat(headers, LEADER_PURCHASE_PRICE_HEADER);
        writeStringHTMLTableColumnTagsClosing(headers);
    }

    if (leaderColumns->salePrice) {
        writeStringHTMLTableColumnTagsOpening(headers);
        strcat(headers, LEADER_SALE_PRICE_HEADER);
        writeStringHTMLTableColumnTagsClosing(headers);
    }

    if (leaderColumns->openingPrice) {
        writeStringHTMLTableColumnTagsOpening(headers);
        strcat(headers, LEADER_OPENING_PRICE_HEADER);
        writeStringHTMLTableColumnTagsClosing(headers);
    }

    if (leaderColumns->maxPrice) {
        writeStringHTMLTableColumnTagsOpening(headers);
        strcat(headers, LEADER_MAX_PRICE_HEADER);
        writeStringHTMLTableColumnTagsClosing(headers);
    }

    if (leaderColumns->minPrice) {
        writeStringHTMLTableColumnTagsOpening(headers);
        strcat(headers, LEADER_MIN_PRICE_HEADER);
        writeStringHTMLTableColumnTagsClosing(headers);
    }
    writeStringHTMLTableRowTagsClosing(headers);
    writeStringHTMLTableHeaderTagsClosing(headers);
}

void
buildLeaderHTMLLine(Leader *leader, char *line, ExporterColumns *leaderColumns, Format **formats, int formats_length) {
    char buffer[LINE_LIMIT];
    strcpy(line, "");

    writeStringHTMLTableRowTagsOpeningAndApplyFormats(leader, line, formats, formats_length);

    if (leaderColumns->specie) {
        writeStringHTMLTableColumnTagsOpening(line);
        sprintf(buffer, "%s", leader->specie);
        strcat(line, buffer);
        writeStringHTMLTableColumnTagsClosing(line);
    }

    if (leaderColumns->variation) {
        writeStringHTMLTableColumnTagsOpening(line);
        sprintf(buffer, "%f", leader->variation);
        strcat(line, buffer);
        writeStringHTMLTableColumnTagsClosing(line);
    }

    if (leaderColumns->purchasePrice) {
        writeStringHTMLTableColumnTagsOpening(line);
        sprintf(buffer, "%f", leader->purchasePrice);
        strcat(line, buffer);
        writeStringHTMLTableColumnTagsClosing(line);
    }

    if (leaderColumns->salePrice) {
        writeStringHTMLTableColumnTagsOpening(line);
        sprintf(buffer, "%f", leader->salePrice);
        strcat(line, buffer);
        writeStringHTMLTableColumnTagsClosing(line);
    }

    if (leaderColumns->openingPrice) {
        writeStringHTMLTableColumnTagsOpening(line);
        sprintf(buffer, "%f", leader->openingPrice);
        strcat(line, buffer);
        writeStringHTMLTableColumnTagsClosing(line);
    }

    if (leaderColumns->maxPrice) {
        writeStringHTMLTableColumnTagsOpening(line);
        sprintf(buffer, "%f", leader->maxPrice);
        strcat(line, buffer);
        writeStringHTMLTableColumnTagsClosing(line);
    }

    if (leaderColumns->minPrice) {
        writeStringHTMLTableColumnTagsOpening(line);
        sprintf(buffer, "%f", leader->minPrice);
        strcat(line, buffer);
        writeStringHTMLTableColumnTagsClosing(line);
    }
    writeStringHTMLTableRowTagsClosing(line);
}

void writeHTMLMainTagsOpening(FILE *output) {
    fprintf(output, "<html><body>");
}

void writeHTMLMainTagsClosing(FILE *output) {
    fprintf(output, "</body></html>");
}

void writeHTMLTableTagOpening(FILE *output) {
    fprintf(output, "<table>");
}

void writeHTMLTableTagClosing(FILE *output) {
    fprintf(output, "</table>");
}

void writeHTMLTableHeaderTagsOpening(FILE *output) {
    fprintf(output, "<thead>");
}

void writeHTMLTableHeaderTagsClosing(FILE *output) {
    fprintf(output, "</thead>");
}

void writeHTMLTableBodyTagsOpening(FILE *output) {
    fprintf(output, "<tbody>");
}

void writeHTMLTableBodyTagsClosing(FILE *output) {
    fprintf(output, "</tbody>");
}

void writeHTMLTableRowTagsOpening(FILE *output) {
    fprintf(output, "<tr>");
}

void writeHTMLTableRowTagsClosing(FILE *output) {
    fprintf(output, "</tr>");
}

void writeHTMLTableColumnTagsOpening(FILE *output) {
    fprintf(output, "<td>");
}

void writeHTMLTableColumnTagsClosing(FILE *output) {
    fprintf(output, "</td>");
}

void writeStringHTMLMainTagsOpening(char *output) {
    strcat(output, "<html><body>");
}

void writeStringHTMLMainTagsClosing(char *output) {
    strcat(output, "</body></html>");
}

void writeStringHTMLTableTagOpening(char *output) {
    strcat(output, "<table>");
}

void writeStringHTMLTableTagClosing(char *output) {
    strcat(output, "</table>");
}

void writeStringHTMLTableHeaderTagsOpening(char *output) {
    strcat(output, "<thead>");
}

void writeStringHTMLTableHeaderTagsClosing(char *output) {
    strcat(output, "</thead>");
}

void writeStringHTMLTableBodyTagsOpening(char *output) {
    strcat(output, "<tbody>");
}

void writeStringHTMLTableBodyTagsClosing(char *output) {
    strcat(output, "</tbody>");
}

void writeStringHTMLTableRowTagsOpeningAndApplyFormats(Leader *leader, char *output, Format **formats_conditions, int formats_conditions_length) {
    for(int i = 0 ; i< formats_conditions_length ; i++){
        FormatCondition format_condition = formats_conditions[i];
        Format *format = format_condition(leader);

        if(format != NULL){
             writePropertyAndValueInTableRowTagOpening(output, format);
        }
    }
}

void writePropertyAndValueInTableRowTagOpening(char *output, Format *format) {
    if (format->apply_component == COMPONENT_TR) { //Iterar esto para solo filtrar los que son TR en la función anterior
        char buffer[50];
        sprintf(buffer, "<tr %s=\"%s\">", format->identifier, format->value);
        strcat(output, buffer);
    }
}

void writeStringHTMLTableRowTagsOpening(char *output) {
    strcat(output, "<tr>");
}

void writeStringHTMLTableRowTagsClosing(char *output) {
    strcat(output, "</tr>");
}

void writeStringHTMLTableColumnTagsOpening(char *output) {
    strcat(output, "<td>");
}

void writeStringHTMLTableColumnTagsClosing(char *output) {
    strcat(output, "</td>");
}