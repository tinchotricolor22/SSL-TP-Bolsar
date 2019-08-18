#include "formatter.h"
#include "formattertypes.h"
#include "../utils/commons.h"

#define FALSE 0
#define TRUE 1

int buildLeaderRedTRCondition(Formatter* formatter , Leader* leader){
    printf("Antes de hacer el init de la list\n");
    init_list(formatter->format_list,&(formatter->format_list_length),MAX_FORMATS);

    if (leader->purchasePrice > leader->openingPrice && 
        leader->salePrice > leader->openingPrice){
            Format *format = malloc(sizeof *format);
            format->identifier = "bgcolor";
            format->value = "red";
            format->apply_component = COMPONENT_TR;

            printf("antes de agregar el format\n");
            add(formatter->format_list,format,&(formatter->format_list_length),MAX_FORMATS);

        return TRUE;
    }
    return FALSE;
}

Formatter* buildLeaderFormatter(){
    Formatter *formatter = malloc(sizeof *formatter);
    
    Format **formats  = malloc(MAX_FORMATS * sizeof formats[0]);
    formatter->format_list = formats;
    formatter->format_list_length = 0;
    formatter->formatCondition = buildLeaderRedTRCondition;
    return formatter;
}

