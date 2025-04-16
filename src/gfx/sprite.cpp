#ifndef SPRITE_CPP
#define SPRITE_CPP

#include <iostream>

#include <glm/gtc/type_ptr.hpp>

#include "sprite.hpp"
#include "../utils/game.hpp"

Sprite::Sprite(Texture &texture) : texture{texture} {
    mesh = Mesh::GetQuadMesh();
}

void Sprite::Draw(Shader &shader, glm::vec3 position){
    shader.Use();
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glActiveTexture(GL_TEXTURE0);
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    shader.SetMat4("model", false, glm::value_ptr(model));
    shader.SetMat4("view", false, Game::camera.GetViewMatrice());
    shader.SetMat4("projection", false, Game::camera.GetProjectionMatrice());
    
    shader.SetVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
    
    mesh.Draw(shader);
}


#endif