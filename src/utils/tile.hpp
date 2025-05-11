#ifndef TILE_HPP
#define TILE_HPP

#include "../gfx/sprite.hpp"

enum TileType{
    GROUND,
    FARM,
};

struct TileTags{
    bool can_harvest;
    bool occupied;
};


class Tile{
    private:
    public:
        glm::ivec2 position;
        enum TileType type;
        Sprite sprite;

        TileTags tags{ 0, 0};        

        Tile(glm::ivec2 position, enum TileType type);

        void Draw(Shader &shader) const;
};


#endif