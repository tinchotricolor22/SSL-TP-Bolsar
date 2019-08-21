#include "formattertypes.h"

#define MAX_FORMATS 10

int buildLeaderRedTRCondition(Formatter *formatter, Leader *leader);

Formatter *buildLeaderFormatter(int (*formatCondition)(struct Formatter *, void *));