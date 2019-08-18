#ifndef LEADER_HEADER
#define LEADER_HEADER

typedef struct Leader {
    char specie[100];
    double variation;
    double purchasePrice;
    double salePrice;
    double openingPrice;
    double maxPrice;
    double minPrice;
} Leader;

#endif