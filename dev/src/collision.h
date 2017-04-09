#ifndef COLLISION_H
#define COLLISION_H

#include "vector.h"


struct collision{
    double d;
    bool valid;
    vector4 point;
    vector4 normal;
    vector4 color;
    vector4 colorp;
    double reflection;
};


#endif // COLLISION_H
