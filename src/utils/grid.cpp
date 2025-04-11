#ifndef GRID_CPP
#define GRID_CPP

#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtx/string_cast.hpp>

#include <iostream> 
#include <cmath>

#include "game.hpp"
#include "grid.hpp"

glm::vec3 Grid::ScreenToWorld(){
    int w, h;
    double xpos, ypos;
    glm::mat4 proj = (glm::mat4)*Game::camera.GetProjectionMatrice();
    glm::mat4 view = (glm::mat4)*Game::camera.GetViewMatrice();
    glm::vec4 res;
    
    glfwGetCursorPos(Game::window, &xpos, &ypos);
    glfwGetWindowSize(Game::window, &w, &h);

    proj = glm::inverse(proj);
    view = glm::inverse(view);

    float worldXPos = (xpos / w - 0.5f) * 2.0f * Game::camera.position.z;
    float worldYPos = -(ypos / h - 0.5f) * 2.0f / Game::camera.ratio * Game::camera.position.z;

    res = view * (proj * glm::vec4(worldXPos, worldYPos, 0.0f, 0.0f)) + glm::vec4(Game::camera.position, 0.0f);
    res.z = 0;
    return res;
}

glm::vec3 Grid::WorldToGrid(glm::vec3 pos){
    glm::vec3 res = glm::floor(pos + 0.5f);
    std::cout << to_string(res) << std::endl;
    return res;   
}  

#endif