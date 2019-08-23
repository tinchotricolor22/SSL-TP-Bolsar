//Cambiar nombre a formatter_leader
#include "formatter.h"
#include "stdlib.h"

Format* leader_purchase_sale_major_opening(Leader *leader) {
    if (leader->purchasePrice > leader->openingPrice &&
        leader->salePrice > leader->openingPrice) {

        Format *format = malloc(sizeof *format);
        format->identifier = "bgcolor";
        format->value = "red";
        format->apply_component = COMPONENT_TR;

        return format;
    }
    return NULL ;
}