//Cambiar nombre a formatter_leader
#include "formatter.h"
#include "stdlib.h"

Format *_leader_purchase_sale_major_opening(Leader *p_leader) {
    if (p_leader->purchase_price > p_leader->opening_price &&
        p_leader->sale_price > p_leader->opening_price) {

        Format *p_format = malloc(sizeof *p_format);
        p_format->identifier = "bgcolor";
        p_format->value = "red";
        p_format->apply_component = COMPONENT_TR;

        return p_format;
    }
    return NULL;
}