#ifndef TILE_CPP
#define TILE_CPP

#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "tile.hpp"
#include "../game.hpp"

Tile::Tile(glm::ivec2 position, TileType type) : 
    position{position}, type{type} {
    switch(type){
        case GROUND:
            sprite.texture = &Game::textureList.textures[(int)GROUND_TEX_B + rand() % (GROUND_TEX_E + 1)];
            tags.occupied = false;
            tags.can_harvest = false;
            break;
        case FARM:
            sprite.texture = &Game::textureList.textures[(int)FARM_TEX];
            tags.occupied = false;
            tags.can_harvest = true;
            break;
        default:
            break;
    }
}

void Tile::Draw(Shader &shader) const{
    shader.Use();
    shader.SetInt("occupied", tags.occupied);
    shader.SetIvec2("tilePos", position);
    sprite.Draw(shader, glm::vec3{position, 0.0f}, glm::vec3{1.0f});
}


#endif