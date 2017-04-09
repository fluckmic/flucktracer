#include "light.h"

light::light(vector4 pos, double i)
{
    posW = pos;
    intensity = i;
}

double light::getIntensity(double d){
    return this->intensity;
}
void light::setPos(vector4 pos){
    this->posW = pos;
}
vector4 light::getPosC(){
    return this->posC;
}
vector4 light::getPosW(){
    return this->posW;
}
void light::to_camera_base(const matrix4 &mat){
    posC = mat*posW;
}
