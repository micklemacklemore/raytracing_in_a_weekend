#ifndef VEC3_H  // #ifndef and #endif are used as 'include guards', it prevents headers from being included twice.
#define VEC3_H  // NOTE: similar to #pragma once?

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {
    public: 
        double e[3];
    public:  // methods
        vec3() : e{0, 0, 0} {}
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

        // what is the difference between these two?? What does the & operator do?
        double operator[](int i) const { return e[i];}
        double& operator[](int i) {return e[i]; }

        vec3& operator+=(const vec3 &v) {  // returns vec3 address?
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;  //??
        }

        vec3& operator*=(const double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3& operator/=(const double t) {
            return *this *= 1/t;
        }

        double length() const {
            return sqrt(length_squared());  // length of a vector is ||a|| = sqrt(a . a)
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];  // dot product
        }
        };

// Type aliases for vec3
using point3 = vec3;  // using keyword?
using color = vec3;

// vec3 utility functions
        // probably need this to add to an array??
        inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
            return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
        }

        inline vec3 operator+(const vec3 &u, const vec3 &v) {
            return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
        }

        inline vec3 operator-(const vec3 &u, const vec3 &v) {
            return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
        }

        inline vec3 operator*(const vec3 &u, const vec3 &v) {
            return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
        }

        inline vec3 operator*(double t, const vec3 &v) {
            return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
        }

        inline vec3 operator*(const vec3 &v, double t) {
            return t * v;
        }

        inline vec3 operator/(vec3 v, double t) {
            return (1/t) * v;
        }

        inline double dot(const vec3 &u, const vec3 &v) {
            return u.e[0] * v.e[0] + 
                   u.e[1] * v.e[1] +
                   u.e[2] * v.e[2];
        }

        inline vec3 cross(const vec3 &u, const vec3 &v) {
            // r = ai + bj + ck
            // s = di + ej + fk
            // r x s = (bf - ce)i + (cd - af)j + (ae - bd)k
            return vec3((u.e[1] * v.e[2] - u.e[2] * v.e[1]),  
                        (u.e[2] * v.e[0] - u.e[0] * v.e[2]),
                        (u.e[0] * v.e[1] - u.e[1] * v.e[0]));
        }

        inline vec3 unit_vector(vec3 v) {
            return v / v.length();
        }

#endif