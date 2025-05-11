#ifndef BUTTON_CPP
#define BUTTON_CPP

#include <iostream>


#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "button.hpp"
#include "grid.hpp"
#include "direction.hpp"
#include "../game.hpp"
#include "../entity/pawnstat.hpp"

Button::Button() : enable{true} { state = IDLE; }
Button::Button(glm::vec2 position, glm::vec2 size) : enable{true}, position{position}, size{size} { state = IDLE; }

void Button::SetSprite(enum ButtonState state, Texture &texture){
    sprites[(int)state].texture = &texture;
}

enum ButtonState Button::GetState() { return state; }

void Button::RenderButton(Shader &shader) const{
    glm::vec3 worldPosition = Grid::ScreenToWorld(position);
    glm::vec3 absoluteSize = glm::vec3(size * Game::camera.position.z * 0.2f, 1.0f);
    sprites[(int)state].Draw(shader, worldPosition, absoluteSize);
}

void Button::Update(){
    glm::vec3 screenPos = Grid::ScreenToWorld();
    glm::vec3 worldPosition = Grid::ScreenToWorld(position);

    if (!enable) return;
    if (screenPos.x >= worldPosition.x - size.x / 2.0f 
            && screenPos.x <= worldPosition.x + size.x / 2.0f
            && screenPos.y >= worldPosition.y - size.y / 2.0f
            && screenPos.y <= worldPosition.y + size.y / 2.0f)
        state = HOVER;
    else 
        state = IDLE;
    
    if (state == HOVER && glfwGetMouseButton(Game::window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        state = CLICKED;
}


SpawnPawnButton::SpawnPawnButton() : Button{} { }
SpawnPawnButton::SpawnPawnButton(glm::vec2 position, glm::vec2 size, enum PawnType type) : Button{position, size}, type{type} { }
int SpawnPawnButton::Clicked(Player &player, Pawn &pawn, Tilemap &tilemap){
    if (GetState() != CLICKED) return 0;
    Tile *tile = nullptr;
    int i;
    for (i = 0; i < 4; ++i){
        glm::ivec2 position = glm::ivec2(pawn.position) + direction[i];
        tile = tilemap.GetTile(position);
        if (tile && !tile->tags.occupied) break; 
        tile = nullptr;
    }
    if (!tile) return 0; // No tile or all near tile are occupied
    
    int coinsNeeded = stats[type].cost;
    if (player.coins < coinsNeeded) return 0;
    player.coins -= coinsNeeded;
    player.AddPawn(tile->position, type);
    pawn.GetTags().on_cooldown = true;
    tile->tags.occupied = true;
    return 1;
}

TransformLordButton::TransformLordButton() : Button{} { }
TransformLordButton::TransformLordButton(glm::vec2 position, glm::vec2 size) : Button{position, size} { }
int TransformLordButton::Clicked(Player &player, Pawn &pawn, Tilemap &tilemap){
    if (GetState() != CLICKED) return 0;
    if (pawn.GetTags().on_cooldown) return 0;
    Tile *tile = nullptr;
    tile = tilemap.GetTile(glm::ivec2(pawn.position));
    if (!tile) return 0;

    player.RemovePawn(tile->position);
    player.AddPawn(tile->position, CASTLE);
    tile->tags.occupied = true;
    return 1;
}

HarvestButton::HarvestButton() : Button{} { }
HarvestButton::HarvestButton(glm::vec2 position, glm::vec2 size) : Button{position, size} { }
int HarvestButton::Clicked(Player &player, Pawn &pawn){
    if (GetState() != CLICKED) return 0;
    if (pawn.GetTags().on_cooldown) return 0;

    player.coins += pawn.stat.prod;
    pawn.GetTags().on_cooldown = true;
    return 1;
}

EndTurnButton::EndTurnButton() : Button{} { };
EndTurnButton::EndTurnButton(glm::vec2 position, glm::vec2 size) : Button{position, size} { };

int EndTurnButton::Clicked(){
    if (GetState() != CLICKED) return 0;
    return 1;
}






#endif