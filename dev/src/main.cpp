#include <iostream>
#include "vector.h"
#include "vector"
#include "element.h"
#include "camera.h"
#include "light.h"

using namespace std;


int main(int argc, char *argv[])
{

    vector<vector4> points = {vector4 {2,-2,-2,1}, vector4 {2,2,-2,1}, vector4 {-2,2,-2,1}, vector4 {-2,-2,-2,1},
                              vector4 {2,-2,2,1}, vector4 {2,2,2,1}, vector4 {-2,2,2,1}, vector4 {-2,-2,2,1}};

    vector<vector4> points2 = {vector4 {10,-10,0,1}, vector4 {10,10,0,1}, vector4 {-10,-10,0,1}, vector4 {-10,10,0,1}};

    vector<vector4> triangles = {vector4 {0,1,4,-1}, vector4 {1,4,5,-1}, vector4 {1,5,2,-1},
                                 vector4 {2,7,6,-1}, vector4 {7,2,3,-1}, vector4 {3,7,4,-1}, vector4 {0,3,4,-1},
                                 vector4 {5,6,7,-1}, vector4 {4,5,7,-1}, vector4 {0,1,3,-1}, vector4 {1,2,3,-1},
                                 vector4 {2,5,6,-1}};

    vector<vector4> triangles2 = {vector4 {0,1,3,0}, vector4 {0,2,3,1}};

    light l1 = light(vector4 {-4,1,6.25,1},0.75);
    light l2 = light(vector4 {4,0,4,1},0.2);

    element e1 = element(triangles, points, matrix4::eye);
    element e2 = element(triangles, points, matrix4::eye);
    element ground = element(triangles2, points2, matrix4::eye);
    element wall_b = element(triangles2, points2, matrix4::eye);
    element wall_l = element(triangles2, points2, matrix4::eye);
    element wall_r = element(triangles2, points2, matrix4::eye);
    element top = element(triangles2, points2, matrix4::eye);
    element wall_f = element(triangles2, points2, matrix4::eye);

    e1.color = vector4 {1,0,0,0};
    e2.color = vector4 {0,0,1,0};
    ground.color = vector4 {1,1,1,0};
    wall_b.color = vector4 {1,1,1,0};
    wall_l.color = vector4 {1,1,1,0};
    wall_r.color = vector4 {1,1,1,0};
    top.color = vector4 {1,1,1,0};
    wall_f.color = vector4 {1,1,1,0};

    wall_l.reflection = 0.2;
    ground.reflection = 0.2;

    wall_b.transform_world(matrix4::trans_t(vector4 {0,10,10,1})*matrix4::rot_x(PI/2));
    wall_l.transform_world(matrix4::trans_t(vector4 {-10,0,10,1})*matrix4::rot_y(PI/2));
    wall_r.transform_world(matrix4::trans_t(vector4 {10,0,10,1})*matrix4::rot_y(PI/2));
    top.transform_world(matrix4::trans_t(vector4 {0,0,10,1}));

    e1.transform_world(matrix4::trans_t(vector4 {2,3,2,1}));
    e1.transform_local(matrix4::rot_z(PI/4));
    e1.transform_local(matrix4::rot_z(PI));

    e2.transform_local(matrix4::scale_s(vector4 {0.5,0.5,0.5,1}));
    e2.transform_world(matrix4::trans_t(vector4 {2,3,5,1}));
    e2.transform_local(matrix4::rot_z(-PI/6));

    vector<element> elements = {e1, e2, ground, wall_b, wall_r, wall_l};
    vector<light> lights = {l1};

    camera cam = camera(elements, lights);
    cam.setPosition(vector4 {1,-14,12,1});
    cam.setPOI(vector4 {-2,5,0,1});

    cam.click();

    return 0;
}
