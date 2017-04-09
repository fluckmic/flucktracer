#ifndef LIGHT_H
#define LIGHT_H

#include "vector.h"

class light
{
public:
    light(vector4 pos, double i);

    double getIntensity(double d);
    void setPos(vector4 pos);
    void to_camera_base(const matrix4 &mat);
    vector4 getPosW();
    vector4 getPosC();

private:

    vector4 posC;
    vector4 posW;
    double intensity;

};

#endif // light_H
