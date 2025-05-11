#ifndef TEXTURE_HPP
#define TEXTURE_HPP


#include <glad/glad.h>

#include <vector>

enum TextureIndex {

    // Tile Sprite
    GROUND_TEX_B = 0,
    GROUND_TEX_E = 3,
    FARM_TEX,
    
    // Pawn Sprite
    CASTLE_TEX,
    WARRIOR_TEX,
    LORD_TEX,
    FARMER_TEX,
    
    // ButtonSprite
    ICASTLE_TEX,
    HCASTLE_TEX,
    CCASTLE_TEX,
    
    IWARRIOR_TEX,
    HWARRIOR_TEX,
    CWARRIOR_TEX,
    
    ILORD_TEX,
    HLORD_TEX,
    CLORD_TEX,
    
    IFARMER_TEX,
    HFARMER_TEX,
    CFARMER_TEX,

    ISKIP_TEX,
    HSKIP_TEX,
    CSKIP_TEX,
    
    COIN_TEX,
};

class Texture{
    public:
        unsigned int id;
        GLenum type;
        int width;
        int height;
    
        Texture();
        Texture(const char *imagePath, GLenum format);
        
        void Destroy();
        void LoadTexture(const char *imagePath, GLenum format);
};

class TextureList{
    public: 
        std::vector<Texture> textures;
    
        void Destroy();
        void LoadTexture();

        Texture &operator[](int pos);
};

#endif