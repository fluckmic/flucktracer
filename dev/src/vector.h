#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>

struct vector4{

    vector4() = default;
    vector4(double _x, double _y, double _z, double _w) :
        x(_x), y(_y), z(_z), w(_w) {}

    double x{0}, y{0}, z{0}, w{1};

    double& operator [](int);
    const double& operator [](int) const;

    double len() const;

    void normalize();

};

    vector4 operator *(const double &, const vector4 &);
    vector4 operator *(const vector4 &, const double &);
    vector4 operator +(const vector4 &, const vector4 &);
    vector4 operator -(const vector4 &, const vector4 &);

    std::ostream &operator<<(std::ostream &os, const vector4 &v);

    double scal_prod(const vector4 &, const vector4 &);
    vector4 cross_prod(const vector4 &, const vector4 &);

struct matrix4{

    matrix4() = default;
    matrix4(vector4 _a, vector4 _b, vector4 _c, vector4 _d) :
        a(_a), b(_b), c(_c), d(_d) {}

    vector4 a, b, c, d;

    vector4& operator [](int);
    const vector4& operator [](int) const;

    void transpose();

    static matrix4 rot_x(double);
    static matrix4 rot_y(double);
    static matrix4 rot_z(double);
    static matrix4 rot_u(const vector4 &, double);

    static matrix4 trans_t(const vector4 &);
    static matrix4 scale_s(const vector4 &);

    static matrix4 eye;
};

    matrix4 operator *(const matrix4 &, const matrix4 &);
    vector4 operator *(const matrix4 &, const vector4 &);

    std::ostream &operator<<(std::ostream &os, const matrix4 &m);

#endif // VECTOR_H
