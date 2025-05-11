#ifndef PAWN_HPP
#define PAWN_HPP

#include <glm/glm.hpp>

#include "pawnstat.hpp"
#include "../gfx/sprite.hpp"
#include "../utils/tilemap.hpp"

enum PawnType {CASTLE, WARRIOR, LORD, FARMER};

struct PawnTags{
    bool can_attack;
    bool can_move;
    bool can_prod;
    bool can_harvest;
    bool on_cooldown;
};

class Pawn{
    private:
        Sprite sprite;


    protected:
        int initMp;
        int initHp;
        
        PawnTags tags;
        
    public:
        PawnType type;
    
        PawnStat stat;

        glm::vec3 position;

        Pawn(int hp, int power, int cost, int prod, int mp, int range, PawnType type, Sprite sprite, glm::vec3 position);
        Pawn(PawnStat stat, PawnType type, Sprite sprite, glm::vec3 position);
        virtual ~Pawn();
        
        virtual void Reset();
        int Move(glm::vec3 newPosition, Tilemap &tilemap);
        void Attack(Pawn &pawn, Tilemap &tilemap);
        void Generate(int &coins); 

        bool IsDead() const;

        PawnTags& GetTags();

        void Draw(Shader &shader) const;
};

class Castle : public Pawn{
    public:

        Castle(glm::vec3 position);

        void Reset();
};

class Warrior : public Pawn{
    public:
        Warrior(glm::vec3 position);

        void Reset();
};

class Lord : public Pawn{
    public:
        Lord(glm::vec3 position);

        void Reset();
};

class Farmer : public Pawn{
    public:
        Farmer(glm::vec3 position);

        void Reset();
};
#endif
