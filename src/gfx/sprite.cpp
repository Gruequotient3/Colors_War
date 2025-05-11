#ifndef SPRITE_CPP
#define SPRITE_CPP

#include <iostream>

#include <glm/gtc/type_ptr.hpp>

#include "sprite.hpp"
#include "../game.hpp"

Mesh Sprite::mesh = Mesh::GetQuadMesh();
Sprite::Sprite() : texture{nullptr} { }
Sprite::Sprite(Texture &texture) : texture{&texture} { }

void Sprite::Draw(Shader &shader, glm::vec3 position, glm::vec3 scale) const{
    shader.Use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    shader.SetMat4("model", false, glm::value_ptr(model));
    shader.SetMat4("view", false, Game::camera.GetViewMatrice());
    shader.SetMat4("projection", false, Game::camera.GetProjectionMatrice());
    
    mesh.Draw(shader);
}


#endif