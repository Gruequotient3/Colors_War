#ifndef DIRECTION_HPP
#define DIRECTION_HPP

#include <glm/glm.hpp>

enum Direction{NORTH, EAST, SOUTH, WEST};

static const glm::ivec2 direction[4] {
    { 0,  1},
    { 1,  0},
    { 0, -1},
    {-1,  0},
};

#endif