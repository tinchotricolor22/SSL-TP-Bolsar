#ifndef LEADER_HEADER
#define LEADER_HEADER

//Leader represents a leader entity
typedef struct Leader {
    char specie[100];
    double variation;
    double purchase_price;
    double sale_price;
    double opening_price;
    double max_price;
    double min_price;
} Leader;

#endif