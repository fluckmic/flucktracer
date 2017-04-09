#ifndef ELEMENT_H
#define ELEMENT_H

#include "vector.h"
#include "collision.h"
#include "ray.h"
#include "vector"
#include <cmath>
#include <limits>

using namespace std;

const double PI  = 3.141592653589793238463;

class element
{
public:
    element(vector<vector4> triangles, vector<vector4> vertices_b, matrix4 base);

    void to_camera_base(const matrix4 &A);
    void transform_local(const matrix4 &A);
    void transform_world(const matrix4 &A);
    collision hit_by_ray(const ray &r);

    matrix4 base;

    vector4 color = {1, 1, 1, 0};
    vector4 colorp = {1, 1, 1, 2};
    double reflection = 0;

private:
    void transform(const matrix4 &A, vector<vector4> &p);
    collision hit_by_ray_triangle(vector4 &ori, vector4 &dir, vector4 &tr);

    vector<vector4> triangles;
    vector<vector4> vertices_b;
    vector<vector4> vertices_c;
    int nmbTriangles;
};

#endif // ELEMENT_H
