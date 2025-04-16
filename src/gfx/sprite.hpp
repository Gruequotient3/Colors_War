#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "../utils/mesh.hpp"
#include "texture.hpp"

class Sprite{
    private:
    public:
        Mesh mesh;
        Texture texture;
        
        Sprite(Texture &texture);
        
        void Draw(Shader &shader, glm::vec3 position);
};

#endif