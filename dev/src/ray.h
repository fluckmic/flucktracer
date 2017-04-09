#ifndef RAY_H
#define RAY_H

#include "vector.h"

struct ray{

    ray() = default;
    ray(vector4 o, vector4 d) : origin(o), dir(d) {}

    vector4 origin;
    vector4 dir;
};

#endif // RAY_H
