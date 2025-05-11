#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "../utils/mesh.hpp"
#include "texture.hpp"

class Sprite{
    private:
    public:
        static Mesh mesh;
        Texture *texture;
        
        Sprite();
        Sprite(Texture &texture);
        
        void Draw(Shader &shader, glm::vec3 position, glm::vec3 scale) const;
};

#endif