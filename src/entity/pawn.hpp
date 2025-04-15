#ifndef PAWN_HPP
#define PAWN_HPP

#include <glm/glm.hpp>

#include "../gfx/sprite.hpp"

enum PawnType {PAWN, CASTLE, WARRIOR, LORD, FARMER};

class Pawn{
    public:
        int hp; // Health point
        int power;
        int cost;
        int prod;
        int mp; // Movement point
        PawnType type;

        Sprite sprite;
        
        glm::vec3 position;

        Pawn(int hp, int power, int cost, int prod, int mp, PawnType type, Sprite sprite);
        virtual ~Pawn();

        void Draw(Shader &shader);
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
