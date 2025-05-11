#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <map>

#include "tile.hpp"
#include "vec.hpp"


class Tilemap{
    private:
        int seed;
        int width;
        int height;
    public:
        std::map<glm::ivec2, Tile, CmpVecs> tiles;

        Tilemap(int seed, int width, int height);

        void GenerateTilemap();

        Tile *GetTile(glm::ivec2 position);
        bool IsOccupied(glm::ivec2 position);
        void Draw(Shader &shader);
};


#endif