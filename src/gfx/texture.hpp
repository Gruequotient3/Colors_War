#ifndef TEXTURE_HPP
#define TEXTURE_HPP


#include <glad/glad.h>

#include <vector>

enum TextureIndex {
    GROUND_TEX,
    PAWN_TEX,
    CASTLE_TEX,
    WARRIOR_TEX,
    LORD_TEX,
    FARMER_TEX,
};

class Texture{
    public:
        unsigned int id;
        GLenum type;
        int width;
        int height;
    
        Texture();
        Texture(const char *imagePath, GLenum format);
    
        void LoadTexture(const char *imagePath, GLenum format);
};

class TextureList{
    public: 
        std::vector<Texture> textures;

        void LoadTexture(){
            textures.clear();
            textures.push_back(Texture{"res/img/ground.jpeg", GL_RGB}); // Ground
            textures.push_back(Texture{"res/img/ground.jpeg", GL_RGB}); // Pawn
            textures.push_back(Texture{"res/img/ground.jpeg", GL_RGB}); // Castle
            textures.push_back(Texture{"res/img/ground.jpeg", GL_RGB}); // Warrior
            textures.push_back(Texture{"res/img/ground.jpeg", GL_RGB}); // Lord
            textures.push_back(Texture{"res/img/ground.jpeg", GL_RGB}); // Farmer
        }
};

#endif