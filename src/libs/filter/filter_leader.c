#include "filter.h"
#include "stdlib.h"
#include "../utils/commons.h"
#include "../domain/leader.h"

FilterResult _leader_filter_major_05_variation(const Leader *leader) {
    return leader->variation > 0.5;
}