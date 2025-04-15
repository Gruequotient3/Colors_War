#ifndef PAWN_CPP
#define PAWN_CPP

#include <iostream>

#include <glm/gtc/type_ptr.hpp>

#include "pawn.hpp"

#include "../gfx/shader.hpp"
#include "../utils/game.hpp"

Pawn::Pawn(int hp, int power, int cost, int prod, int mp, PawnType type, Sprite sprite) :
    hp{hp}, power{power}, cost{cost}, prod{prod}, mp{mp}, type{type}, sprite{sprite} { 
    position = glm::vec3(0.0f, 0.0f, 0.0f);
}

Pawn::~Pawn() { }

Castle::Castle() : Pawn{20, 0, 15, 2, 0, CASTLE, Sprite{Game::textureList.textures[(int)CASTLE_TEX]}} { }

Warrior::Warrior() : Pawn{10, 5, 10, 0, 2, WARRIOR, Sprite{Game::textureList.textures[(int)WARRIOR_TEX]}} { }

Lord::Lord() : Pawn{5, 3, 10, 0, 1, LORD, Sprite{Game::textureList.textures[(int)LORD_TEX]}} { }

Farmer::Farmer() : Pawn{1, 0, 20, 5, 2, FARMER, Sprite{Game::textureList.textures[(int)FARMER_TEX]}} { }

void Pawn::Draw(Shader &shader){
    sprite.Draw(shader, position);
}


#endif
