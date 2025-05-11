#ifndef TEXTURE_CPP
#define TEXTURE_CPP

#include <stb_image.h>
#include <iostream>

#include "texture.hpp"


Texture::Texture() : id{0} { }

void Texture::Destroy(){
    if (id) { glDeleteTextures(1, &id); id = 0; }
}

Texture::Texture(const char *imagePath, GLenum format) : id{0} {
    LoadTexture(imagePath, format);
}

void Texture::LoadTexture(const char *imagePath, GLenum format){
    if (id != 0) glDeleteTextures(1, &id);

    type = GL_TEXTURE_2D;
    
    // Create Texture
    glGenTextures(1, &id);
    glBindTexture(type, id);

    // Texture Parameter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // load image and set to the texture
    stbi_set_flip_vertically_on_load(false);
    int nrChannels;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    unsigned char *data = stbi_load(imagePath, &width, &height, &nrChannels, STBI_rgb_alpha);
    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout << "Failed to load texture" << std::endl;
        std::cout << stbi_failure_reason() << std::endl;
    }
    stbi_image_free(data);
    glBindTexture(type, 0);
}


void TextureList::Destroy(){
    std::vector<Texture>::iterator it;
    for (it = textures.begin(); it != textures.end(); ++it){
        it->Destroy();
    }
    textures.clear();
}

void TextureList::LoadTexture(){
    Destroy();
    textures.push_back(Texture{"res/img/sprites/ground0.png", GL_RGBA}); // Ground0
    textures.push_back(Texture{"res/img/sprites/ground1.png", GL_RGBA}); // Ground1
    textures.push_back(Texture{"res/img/sprites/ground2.png", GL_RGBA}); // Ground2
    textures.push_back(Texture{"res/img/sprites/ground3.png", GL_RGBA}); // Ground3
    textures.push_back(Texture{"res/img/sprites/farm.png", GL_RGBA}); // FARM (To do)
    textures.push_back(Texture{"res/img/sprites/castle.png", GL_RGBA}); // Castle
    textures.push_back(Texture{"res/img/sprites/warrior.png", GL_RGBA}); // Warrior
    textures.push_back(Texture{"res/img/sprites/lord.png", GL_RGBA}); // Lord
    textures.push_back(Texture{"res/img/sprites/farmer.png", GL_RGBA}); // Farmer
    textures.push_back(Texture{"res/img/button/IdleCastleButton.png", GL_RGBA}); // Castle Button IDLE
    textures.push_back(Texture{"res/img/button/HoverCastleButton.png", GL_RGBA}); // Castle Button Hover
    textures.push_back(Texture{"res/img/button/ClickedCastleButton.png", GL_RGBA}); // Castle Button Clicked
    textures.push_back(Texture{"res/img/button/IdleWarriorButton.png", GL_RGBA}); // Warrior Button IDLE
    textures.push_back(Texture{"res/img/button/HoverWarriorButton.png", GL_RGBA}); // Warrior Button Hover
    textures.push_back(Texture{"res/img/button/ClickedWarriorButton.png", GL_RGBA}); // Warrior Button Clicked
    textures.push_back(Texture{"res/img/button/IdleLordButton.png", GL_RGBA}); // Lord Button IDLE
    textures.push_back(Texture{"res/img/button/HoverLordButton.png", GL_RGBA}); // Lord Button Hover
    textures.push_back(Texture{"res/img/button/ClickedLordButton.png", GL_RGBA}); // Lord Button Clicked
    textures.push_back(Texture{"res/img/button/IdleFarmerButton.png", GL_RGBA}); // Farmer Button IDLE
    textures.push_back(Texture{"res/img/button/HoverFarmerButton.png", GL_RGBA}); // Farmer Button Hover
    textures.push_back(Texture{"res/img/button/ClickedFarmerButton.png", GL_RGBA}); // Skip Button Clicked
    textures.push_back(Texture{"res/img/button/IdleSkipButton.png", GL_RGBA}); // Skip Button Idle
    textures.push_back(Texture{"res/img/button/HoverSkipButton.png", GL_RGBA}); // Skip Button Hover
    textures.push_back(Texture{"res/img/button/ClickedSkipButton.png", GL_RGBA}); // Skip Button Clicked
    textures.push_back(Texture{"res/img/sprites/coin.png", GL_RGBA}); // Coin (To do)
}

Texture &TextureList::operator[](int pos){
    if (pos < 0 || pos >= (int)textures.size()) exit(EXIT_FAILURE);
    return textures[pos];
}


#endif