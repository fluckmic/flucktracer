#include "element.h"

element::element(vector<vector4> triangles, vector<vector4> vertices_b, matrix4 base){
    this->triangles = triangles;
    this->vertices_b = vertices_b;
    this->vertices_c = vertices_b;
    this->base = base;
    this->nmbTriangles = triangles.size();
}

void element::to_camera_base(const matrix4 &A){
    for(unsigned int i = 0; i < this->vertices_b.size(); i++)
        vertices_c.at(i) = A*vertices_b.at(i);
}

void element::transform_local(const matrix4 &A){
    for(unsigned int i = 0; i < this->vertices_b.size(); i++)
        vertices_b.at(i) = A*vertices_b.at(i);
}

void element::transform_world(const matrix4 &A){
    this->base = A*this->base;
}

collision element::hit_by_ray(const ray &r){
    vector4 dir = r.dir;
    vector4 ori = r.origin;

    collision c, cc;
    c.d = numeric_limits<double>::max(); c.valid = false;

    for(int i = 0; i < nmbTriangles; i++){
        cc = hit_by_ray_triangle(ori, dir, triangles.at(i));
        if(cc.d < c.d && cc.valid)
                c = cc;
    }
    c.color = color; c.colorp = colorp; c.reflection = reflection;
    return c;
}


collision element::hit_by_ray_triangle(vector4 &ori, vector4 &dir, vector4 &tr){

    collision ret;

    bool inside = false;

    vector4 v1 = vertices_c[tr.x];
    vector4 v2 = vertices_c[tr.y];
    vector4 v3 = vertices_c[tr.z];

    vector4 u = v2-v1; u.normalize();
    vector4 v = v3-v1; v.normalize();

    vector4 n = cross_prod(u,v); n.normalize();

    if( scal_prod(n,dir) > 0)
        n = (-1)*n;

    double d = (scal_prod(n,v1)-(scal_prod(ori,n)))/(scal_prod(dir,n));
    vector4 pc;

    if(d > 0.0001 && d < numeric_limits<double>::max()){

        pc = ori+dir*d;

        double A3 = cross_prod((pc-v1),(v2-v1)).len()/2;
        double A2 = cross_prod((pc-v1),(v3-v1)).len()/2;
        double A1 = cross_prod((pc-v2),(v3-v2)).len()/2;
        double A = cross_prod((v2-v1),(v3-v1)).len()/2;

        double s3 = A3/A; double s2 = A2/A;
        double s1 = A1/A; double err = fabs(1.-(s1+s2+s3));

        inside = (0 < s1) && (s1 < 1) && (0 < s2) &&
                 (s2 < 1) && (0 < s3) && (s3 < 1) &&
                 err < (3*std::numeric_limits<double>::epsilon());
    }

    ret.d = d; ret.point = pc;
    ret.normal = n; ret.valid = inside;
    return ret;

}
