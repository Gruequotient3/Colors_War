#ifndef PAWN_HPP
#define PAWN_HPP

enum PawnType {PAWN, CASTLE, WARRIOR, LORD, FARMER};

class Pawn{
    public:
        int hp; // Health point
        int power;
        int cost;
        int prod;
        int mp; // Movement point
        PawnType type;
        Pawn(int hp, int power, int cost, int prod, int mp, PawnType type);
        virtual ~Pawn();
};

class Castle : public Pawn{
    public:
        Castle();
};

class Warrior : public Pawn{
    public:
        Warrior();
};

class Lord : public Pawn{
    public:
        Lord();
};

class Farmer : public Pawn{
    public:
        Farmer();
};
#endif
