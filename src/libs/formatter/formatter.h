#ifndef FORMATTER_TYPES_HEADER
#define FORMATTER_TYPES_HEADER

#include "../parser/parser.h"
#include "../domain/leader.h"

#define COMPONENT_TR "TR" //debería haber un header para formatter de html
#define MAX_FORMATS 10

typedef char *Component;

typedef struct Format {
    char *identifier;
    char *value;
    Component *apply_component;
} Format;

typedef Format *(*FormatCondition)(void *);

Format *leader_purchase_sale_major_opening(Leader *leader);

#endif