#ifndef RANDOM_H
#define RANDOM_H

#include <chrono> 
#include <random>

namespace rnd {

    float random();
    float random(float lower, float upper);
    int random(int lower, int upper);

}

#endif