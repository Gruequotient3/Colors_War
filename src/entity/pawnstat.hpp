#ifndef PAWN_STAT_HPP
#define PAWN_STAT_HPP

struct PawnStat{
    int hp; // Health point
    int power;
    int cost;
    int prod;
    int mp; // Movement point
    int range;
    int cooldown; 
};


static const PawnStat stats[]{
    PawnStat{20, 0, 15, 2, 0, 0, 0},
    PawnStat{10, 5, 10, 0, 4, 1, 0},
    PawnStat{5, 3, 10, 0, 2, 1, 2},
    PawnStat{1, 0, 10, 5, 3, 0, 0},
};

#endif