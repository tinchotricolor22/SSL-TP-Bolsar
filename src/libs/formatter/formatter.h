#ifndef FORMATTER_TYPES_HEADER
#define FORMATTER_TYPES_HEADER

#include "parser.h"
#include "../domain/leader.h"

#define COMPONENT_TR "TR"
#define MAX_FORMATS 10

//Component represents component that applies the format
typedef char *Component;

//Format represents format entity
typedef struct Format {
    char *identifier;
    char *value;
    Component *apply_component;
} Format;

//FormatCondition represents format condition functions that returns a Format* if
typedef Format *(*FormatCondition)(const void *);

//_leader_purchase_sale_major_opening is a format condition that returns true if leader has purchase and sale > to opening price
Format *_leader_purchase_sale_major_opening(const Leader *);

#endif