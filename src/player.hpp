#ifndef PLAYER_HPP
#define PLAYER_HPP


#include "entity/pawn.hpp"
#include "utils/vec.hpp"
#include "utils/vector.hpp"

class Player{
    private:
    public:
        Vector<Pawn> pawns;
        glm::vec3 color;

        int coins;

        Player();
        void AddPawn(glm::ivec2 position, enum PawnType pawnType);
        void RemovePawn(glm::ivec2 key);
        
        Pawn *GetPawn(glm::ivec2 key);
        bool ContainPawn(Pawn &pawn);
        bool HaveCastle();
        
        void ResetPawn();
        void HarvestCoins();
        
        void RenderPawns(Shader &shader, Pawn *selected);
};

#endif