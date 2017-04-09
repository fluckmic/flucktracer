#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "cmath"
#include "element.h"
#include "light.h"
#include <vector>
#include "raytracer.h"
#include <iostream>
#include <opencv2/opencv.hpp>


class camera
{
public:
    camera(vector<element> elements, vector<light> lights);
    void setPosition(vector4 pos);
    void setPOI(vector4 poi);
    void click();

private:

    vector<element> elements;
    vector<light> lights;

    vector4 n, u, v;

    vector4 up = {0,0,1,1},
            pos = {0,0,0,1},
            poi = {1,1,1,1};

    /**** camera parameter *****/
    const double    angle_vertical_view = PI / 5,
                    dist_to_image_plane = 5,
                    aspect_ratio = 16./9.;

    const int       res_x = 1920,
                    res_y = 1080;

    const double    heigth = 2*tan(angle_vertical_view/2)*dist_to_image_plane,
                    width = aspect_ratio*heigth;

    const double    sx = width/res_x,
                    sy = heigth/res_y;
    /****************************/

    /**** rendering parameter ***/
    int depth = 2;
    /****************************/

    vector4 center = dist_to_image_plane * vector4 {1,0,0,1};
    vector4 origImage = center + ((width/2) * vector4 {0,1,0,1}) - ((heigth/2) * vector4 {0,0,1,1});

    vector4 Pij(int i, int j) {
        vector4 dx = (sx*i) * vector4 {0,-1,0,1};
        vector4 dy = (sy*j) * vector4 {0,0,1,1};
        return origImage + dx + dy;
    }

    void refreshParameter();
    void imageAllocation();
    void imageDealocation();
    void transformElements();

};

#endif // CAMERA_H
