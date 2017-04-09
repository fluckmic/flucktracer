#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "vector.h"
#include <vector>
#include "element.h"
#include "light.h"
#include "ray.h"
#include <limits>

class raytracer
{
public:
    raytracer(vector<element> elements, vector<light> lights);
    vector4 trace(ray r, int depth);

private:
    vector<element> elements;
    vector<light> lights;

};

#endif // RAYTRACER_H
