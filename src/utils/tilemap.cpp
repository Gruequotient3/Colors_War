#ifndef TILEMAP_CPP
#define TILEMAP_CPP

#include <iostream>

#include<glm/gtc/matrix_transform.hpp>

#include "tilemap.hpp"

Tilemap::Tilemap(int seed, int width, int height) : seed{seed}, width{width}, height{height}{ }

void Tilemap::GenerateTilemap(){
    srand(seed);
    int boundaryX = width/2;
    int boundaryY = height/2;
    int i = 0;
    for (int y = -boundaryY; y <= boundaryY; ++y){
        for (int x = -boundaryX; x <= boundaryX; ++x){
            glm::vec2 position{x, y};
            tiles.insert({position, Tile{position, (rand() % 100) < 5 ? FARM : GROUND}});
            ++i;
        }
    }
}

Tile *Tilemap::GetTile(glm::ivec2 position){
    std::map<glm::ivec2, Tile>::iterator it;
    for (it = tiles.begin(); it != tiles.end(); ++it){
        if (position == it->first) return &it->second;
    }
    return nullptr;
}

void Tilemap::Draw(Shader &shader){
    shader.Use();
    shader.SetInt("outlined", 0);
    std::map<glm::ivec2, Tile>::iterator it;
    for (it = tiles.begin(); it != tiles.end(); ++it){
        it->second.Draw(shader);
    }
}

#endif