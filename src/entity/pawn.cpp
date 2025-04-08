#ifndef PAWN_CPP
#define PAWN_CPP

#include "pawn.hpp"

Pawn::Pawn(int hp, int power, int cost, int prod, int mp, PawnType type = PAWN) :
    hp{hp}, power{power}, cost{cost}, prod{prod}, mp{mp}, type{type} { }

Pawn::~Pawn() { }

Castle::Castle() : Pawn{20, 0, 15, 2, 0, CASTLE} { }

Warrior::Warrior() : Pawn{10, 5, 10, 0, 2, WARRIOR} { }

Lord::Lord() : Pawn{5, 3, 10, 0, 1, LORD} { }

Farmer::Farmer() : Pawn{1, 0, 20, 5, 2, FARMER} { }


#endif
