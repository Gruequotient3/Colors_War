#ifndef VEC_HPP
#define VEC_HPP

#include <glm/glm.hpp>

struct CmpVecs{
    bool operator()(const glm::vec2 &a, const glm::vec2 &b) const{
        if (a.x < b.x) return true;
        return a.y < b.y; 
    }
};

#endif