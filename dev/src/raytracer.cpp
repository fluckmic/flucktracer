#include "raytracer.h"

const double Iambient = 0.2;

raytracer::raytracer(vector<element> elements, vector<light> lights)
{
    this->elements = elements;
    this->lights = lights;
}


vector4 raytracer::trace(ray r, int depth){

    vector4 retColor{0,0,0,1};
    collision c = {numeric_limits<double>::max(),false};

    for(int i = 0; i < elements.size(); i++){
        element e = elements.at(i);
        collision cc = e.hit_by_ray(r);
        if(cc.valid && cc.d < c.d)
            c = cc;
    }

    if(!c.valid)
        return retColor;

    retColor = c.color;
    double I = 0.;

    vector4 dl, dc, dn;

    bool totShadow = true;
    for(unsigned int i = 0; i < lights.size(); i++){

        light l = lights.at(i);

        dl = l.getPosC() - c.point;
        dc = c.point; dc.normalize();
        dn = c.normal;
        double disl = dl.len(); dl.normalize();

        ray sr = {c.point, dl};

        bool inShadow = false;
        for(int i = 0; i < elements.size(); i++){
            element e = elements.at(i);
            collision scc = e.hit_by_ray(sr);
            if(scc.valid && scc.d < disl){
                inShadow = true;
                break;
            }
        }

        if(inShadow)
            continue;

        totShadow = false;

        double Il = l.getIntensity(disl) * 255;

        // diffuse intensity
        double df = scal_prod(dl, c.normal);
        if(df > 0)
            I = I + (c.colorp.y* df *Il);

        // reflection intensity
        double kr = scal_prod(((2*dn*(scal_prod(dn,dl)))-dl),dc);
        if(kr > 0){
           kr = pow(kr, c.colorp.w);
           I = I + (c.colorp.z * kr * Il);
        }

    }

    if(totShadow)
        return vector4 {0,0,0,0};

    // ambient intensity
    I = I + (Iambient * 255 * c.colorp.x);

    retColor = retColor*I;

    // return since no reflection
    if(!(c.reflection > 0))
        return retColor;

    // return if depth = 1
    if(depth == 1)
        return retColor;

    vector4 dr = (2*dn*(scal_prod(dn,dl)))-dl; dr.normalize();
    r.origin = c.point; r.dir = dr;

    vector4 refColor =  this->trace(r, depth-1);
    retColor = ((1-c.reflection) *retColor) + (c.reflection * refColor);
    return retColor;
}
