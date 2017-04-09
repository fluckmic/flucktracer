#include "vector.h"

    double& vector4::operator [](int i){
        switch(i){
        case 1: return y; break;
        case 2: return z; break;
        case 3: return w; break;
        default: return x;
        }
    }

    const double& vector4::operator [](int i) const {
        switch(i){
        case 1: return y; break;
        case 2: return z; break;
        case 3: return w; break;
        default: return x;
        }
    }

    vector4 operator *(const double &s, const vector4 &v){
        return vector4(s*v.x, s*v.y, s*v.z, 1);
    }

    vector4 operator *(const vector4 &v, const double &s){
        return s*v;
    }

    vector4 operator +(const vector4 &v1, const vector4 &v2){
        return vector4( v1.x+v2.x,
                        v1.y+v2.y,
                        v1.z+v2.z,
                        1 );
    }

    vector4 operator -(const vector4 &v1, const vector4 &v2){
        return vector4( v1.x-v2.x,
                        v1.y-v2.y,
                        v1.z-v2.z,
                        1 );
    }

    std::ostream &operator<<(std::ostream &os, const vector4 &v){
        os << v.x << "\n" << v.y << "\n" << v.z << "\n" << v.w << std::endl;
        return os;
    }

    double scal_prod(const vector4 &v1, const vector4 &v2){
         return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
    }

    vector4 cross_prod(const vector4 &v1, const vector4 &v2){
        return vector4( v1.y*v2.z - v1.z*v2.y,
                        v1.z*v2.x - v1.x*v2.z,
                        v1.x*v2.y - v1.y*v2.x,
                        1 );
    }

   double vector4::len() const {
       return sqrt(x*x+y*y+z*z);
   }

   void vector4::normalize() {
       double l = 1/len();
       x=l*x; y=l*y; z=l*z;
   }

   void matrix4::transpose(){
       vector4 ta = a; vector4 tb = b;
       vector4 tc = c; vector4 td = d;
       a = {ta.x, tb.x, tc.x, td.x};
       b = {ta.y, tb.y, tc.y, td.y};
       c = {ta.z, tb.z, tc.z, td.z};
       d = {ta.w, tb.w, tc.w, td.w};
   }

   vector4& matrix4::operator [](int i){
       switch (i) {
       case 1: return b;
       case 2: return c;
       case 3: return d;
       default: return a;
       }
   }

   const vector4& matrix4::operator [](int i) const {
       switch (i) {
       case 1: return b;
       case 2: return c;
       case 3: return d;
       default: return a;
       }
   }

   matrix4 matrix4::matrix4::eye = {
       vector4{1,0,0,0},
       vector4{0,1,0,0},
       vector4{0,0,1,0},
       vector4{0,0,0,1}
   };

   matrix4 matrix4::rot_x(double angle_rad){
        matrix4 ret = matrix4::eye;
        ret[1][1] = cos(angle_rad);
        ret[1][2] = sin(angle_rad);
        ret[2][1] = -sin(angle_rad);
        ret[2][2] = cos(angle_rad);
        return ret;
    }

    matrix4 matrix4::rot_y(double angle_rad){
        matrix4 ret = matrix4::eye;
        ret[0][0] = cos(angle_rad);
        ret[0][2] = -sin(angle_rad);
        ret[2][0] = sin(angle_rad);
        ret[2][2] = cos(angle_rad);
        return ret;
    }

    matrix4 matrix4::rot_z(double angle_rad){
        matrix4 ret = matrix4::eye;
        ret[0][0] = cos(angle_rad);
        ret[0][1] = sin(angle_rad);
        ret[1][0] = -sin(angle_rad);
        ret[1][1] = cos(angle_rad);
        return ret;
    }

    matrix4 matrix4::trans_t(const vector4 &t){
        matrix4 ret = matrix4::eye;
        ret[3] = t; ret[3][3] = 1;
        return ret;
    }

    matrix4 matrix4::scale_s(const vector4 &t){
        matrix4 ret = matrix4::eye;
        ret.a.x = t.x; ret.b.y = t.y; ret.c.z = t.z;
        return ret;
    }

    matrix4 matrix4::rot_u(const vector4 &u, double angle_rad){
        vector4 tu = u; tu.normalize();
        double c = cos(angle_rad); double cc = 1-c;
        double s = sin(angle_rad);
        return matrix4 { {c+u.x*u.x*cc     ,u.y*u.z*cc+u.z*s   ,u.z*u.x*cc-u.y*s   ,0},
                         {u.x*u.y*cc-u.z*s ,c+u.y*u.y*cc       ,u.z*u.y*cc+u.x*s   ,0},
                         {u.x*u.z*cc+u.y*s ,u.y*u.z*cc-u.x*s   ,c+u.z*u.z*cc       ,0},
                         {0                ,0                  ,0                  ,1} };
        }


    matrix4 operator *(const matrix4 &m1, const matrix4 &m2){
        matrix4 tm1 = m1;
        tm1.transpose();
        return {{   scal_prod(tm1.a,m2.a)+tm1.a.w*m2.a.w, scal_prod(tm1.b,m2.a)+tm1.b.w*m2.a.w, scal_prod(tm1.c,m2.a)+tm1.c.w*m2.a.w, scal_prod(tm1.d,m2.a)+tm1.d.w*m2.a.w},
                {   scal_prod(tm1.a,m2.b)+tm1.a.w*m2.b.w, scal_prod(tm1.b,m2.b)+tm1.b.w*m2.b.w, scal_prod(tm1.c,m2.b)+tm1.c.w*m2.b.w, scal_prod(tm1.d,m2.b)+tm1.d.w*m2.b.w},
                {   scal_prod(tm1.a,m2.c)+tm1.a.w*m2.c.w, scal_prod(tm1.b,m2.c)+tm1.b.w*m2.c.w, scal_prod(tm1.c,m2.c)+tm1.c.w*m2.c.w, scal_prod(tm1.d,m2.c)+tm1.d.w*m2.c.w},
                {   scal_prod(tm1.a,m2.d)+tm1.a.w*m2.d.w, scal_prod(tm1.b,m2.d)+tm1.b.w*m2.d.w, scal_prod(tm1.c,m2.d)+tm1.c.w*m2.d.w, scal_prod(tm1.d,m2.d)+tm1.d.w*m2.d.w}};
     }

    vector4 operator *(const matrix4 &m, const vector4 &v){
        matrix4 tm1 = m;
        tm1.transpose();
        return vector4 {scal_prod(tm1.a,v)+tm1.a.w*v.w,
                        scal_prod(tm1.b,v)+tm1.b.w*v.w,
                        scal_prod(tm1.c,v)+tm1.c.w*v.w,
                        scal_prod(tm1.d,v)+tm1.d.w*v.w};
    }

    std::ostream &operator<<(std::ostream &os, const matrix4 &m){
        os << m.a.x << " " << m.b.x << " " << m.c.x << " " << m.d.x << "\n"
           << m.a.y << " " << m.b.y << " " << m.c.y << " " << m.d.y << "\n"
           << m.a.z << " " << m.b.z << " " << m.c.z << " " << m.d.z << "\n"
           << m.a.w << " " << m.b.w << " " << m.c.w << " " << m.d.w << std::endl;
        return os;
    }
