#ifndef GRID_HPP
#define GRID_HPP

#include <glm/glm.hpp>

class Grid{
    public:
        static glm::vec3 ScreenToWorld();
        static glm::vec3 WorldToGrid(glm::vec3 pos);
};


#endif