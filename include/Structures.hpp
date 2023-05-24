#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

#include "defines.hpp"

struct Path
{
    float distance;
    float eta;          // 1/distance (inverse of distance)
    float pheromone;
};

#endif /* STRUCTURES_HPP */