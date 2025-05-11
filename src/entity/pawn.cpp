#ifndef PAWN_CPP
#define PAWN_CPP

#include <iostream>

#include <glm/gtc/type_ptr.hpp>

#include "pawn.hpp"

#include "../gfx/shader.hpp"
#include "../utils/grid.hpp"
#include "../utils/direction.hpp"
#include "../game.hpp"

#define INIT_PAWN_TAGS(ATT, MOV, PROD, HARV, ABIL) \
    tags.can_attack = ATT; \
    tags.can_move = MOV; \
    tags.can_prod = PROD; \
    tags.can_harvest = HARV; \
    tags.on_cooldown = ABIL;

Pawn::Pawn(int hp, int power, int cost, int prod, int mp, int range, PawnType type, Sprite sprite, glm::vec3 position) :
        sprite{sprite}, type{type} {
    this->initHp = hp;
    this->initMp = mp;
    this->stat.hp = hp;
    this->stat.power = power;
    this->stat.cost = cost;
    this->stat.prod = prod;
    this->stat.mp = mp;
    this->stat.range = range;

    this->position = position;
}

Pawn::Pawn(PawnStat stat, PawnType type, Sprite sprite, glm::vec3 position) :
        sprite{sprite}, type{type} {
    this->stat = stat;
    this->initHp = stat.hp;
    this->initMp = stat.mp;
    this->position = position;
}

Pawn::~Pawn() { }


void Pawn::Reset(){
    stat.mp = initMp;
}

int Pawn::Move(glm::vec3 newPosition, Tilemap &tilemap){
    Tile *oldTile = nullptr;
    Tile *newTile = nullptr;
    oldTile = tilemap.GetTile(glm::ivec2(position));
    newTile = tilemap.GetTile(glm::ivec2(newPosition));
    
    if (!oldTile || !newTile) return 0;
    if (oldTile == newTile) return 0;

    int mpUse = Grid::Distance(position, newPosition);
    if (stat.mp - mpUse < 0) return 0;
    
    if (oldTile && newTile && !newTile->tags.occupied){
        position = newPosition;
        oldTile->tags.occupied = 0;
        newTile->tags.occupied = 1;
        stat.mp -= mpUse;
    }
    return 1;
}

void Pawn::Attack(Pawn &pawn, Tilemap &tilemap){
    if (!tags.can_attack) return;
    if (Grid::Distance(position, pawn.position) > stat.range){
        bool moved = false;
        int index = 0;
        int minDist = Grid::Distance(position, glm::ivec2(pawn.position) + direction[0]);
        for (int i = 1; i < 4; ++i){
            int dist = Grid::Distance(position, glm::ivec2(pawn.position) + direction[i]);
            if (minDist > dist){
                minDist = dist;
                index = i;
            }
        }
        moved = Move(pawn.position + glm::vec3(direction[index], 0.0f), tilemap);
        if (!moved) return;
    }
    pawn.stat.hp -= stat.power;
    tags.can_attack = false;
}

void Pawn::Generate(int &coins){
    if (!tags.can_prod) return; 
    coins += stat.prod;
    tags.can_prod = false;
}

bool Pawn::IsDead() const{
    if (stat.hp <= 0) return true;
    return false;
}

PawnTags& Pawn::GetTags() { return tags; }

void Pawn::Draw(Shader &shader) const{
    sprite.Draw(shader, position, glm::vec3{1.0f});
}

Castle::Castle(glm::vec3 position) : Pawn{stats[CASTLE], CASTLE, Sprite{Game::textureList.textures[(int)CASTLE_TEX]}, position} { 
    INIT_PAWN_TAGS(false, false, true, false, true);
}

void Castle::Reset(){
    stat.mp = initMp;
    tags.on_cooldown = false;
    tags.can_prod = true;
}

Warrior::Warrior(glm::vec3 position) : Pawn{stats[WARRIOR], WARRIOR, Sprite{Game::textureList.textures[(int)WARRIOR_TEX]}, position} { 
    INIT_PAWN_TAGS(true, true, false, false, true);
}

void Warrior::Reset(){
    stat.mp = initMp;
    tags.can_attack = true;
    tags.on_cooldown = false;  
}

Lord::Lord(glm::vec3 position) : Pawn{stats[LORD], LORD, Sprite{Game::textureList.textures[(int)LORD_TEX]}, position} { 
    INIT_PAWN_TAGS(true, true, false, false, true);
}

void Lord::Reset(){
    stat.mp = initMp;
    tags.can_attack = true;
    if (tags.on_cooldown)
        if (--stat.cooldown <= 0)
            tags.on_cooldown = false; 
    
}

Farmer::Farmer(glm::vec3 position) : Pawn{stats[FARMER], FARMER, Sprite{Game::textureList.textures[(int)FARMER_TEX]}, position} { 
    INIT_PAWN_TAGS(false, true, false, true, true);
}

void Farmer::Reset(){
    stat.mp = initMp;
    tags.on_cooldown = false; 
}




#endif
