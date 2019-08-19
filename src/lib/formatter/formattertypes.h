#ifndef FORMATTER_TYPES_HEADER
#define FORMATTER_TYPES_HEADER

#include "../parser/parsertypes.h"
#include "../domain/leader.h"

#define COMPONENT_TR "TR" //debería haber un header para formatter de html

typedef char *Component;

typedef struct Format {
    char *identifier;
    char *value;
    Component *apply_component;
} Format;

typedef struct Formatter {
    Format **format_list;
    int format_list_length;

    int (*formatCondition)(struct Formatter *, void *);
} Formatter;

typedef int(*FormatCondition)(Formatter *, void *);

#endif