#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "player.hpp"
#include <iostream>

Player::Player() : coins{10} { };
void Player::AddPawn(glm::ivec2 position, enum PawnType pawnType){
    switch (pawnType){
        case CASTLE:
            pawns.Push_back(Castle{glm::vec3(position, 0.0f)});
            break;
        case WARRIOR:
            pawns.Push_back(Warrior{glm::vec3(position, 0.0f)});
            break;
        case LORD:
            pawns.Push_back(Lord{glm::vec3(position, 0.0f)});
            break;
        case FARMER:
            pawns.Push_back(Farmer{glm::vec3(position, 0.0f)});
            break;
    }
}

void Player::RemovePawn(glm::ivec2 key){
    for (unsigned int i = 0; i < pawns.Size(); ++i){
        if (glm::ivec2(pawns[i].position) == key){
            pawns.Erase(i);
            break;
        }
    }
}

Pawn *Player::GetPawn(glm::ivec2 key){
    for (unsigned int i = 0; i < pawns.Size(); ++i){
        if (key == glm::ivec2(pawns[i].position)) return &pawns[i];
    }
    return nullptr;
}

bool Player::ContainPawn(Pawn &pawn){
    if (GetPawn(glm::ivec2(pawn.position))) return true;
    return false;
}

bool Player::HaveCastle(){
    for(unsigned int i = 0; i < pawns.Size(); ++i){
        if (pawns[i].type == CASTLE) return true;
    }
    return false;
}

void Player::ResetPawn(){
    for (unsigned int i = 0; i < pawns.Size(); ++i){
        pawns[i].Reset();
    }
}

void Player::HarvestCoins(){
    for (unsigned int i = 0; i < pawns.Size(); ++i){
        pawns[i].Generate(coins);
    }
}

void Player::RenderPawns(Shader &shader, Pawn *selected){
    shader.Use();
    shader.SetInt("outlined", 1);
    for (unsigned int i = 0; i < pawns.Size(); ++i){
        if (&pawns[i] == selected)
            shader.SetVec3("color", glm::vec3(1.0f));
        else
            shader.SetVec3("color", color);
        
        pawns[i].Draw(shader);
    }
}


#endif