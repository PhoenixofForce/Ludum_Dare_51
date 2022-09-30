#ifndef VEC2F_H
#define VEC2F_H

#include <tgmath.h>
#include <cassert>

namespace vec {
    class vec2f {

    public:
        float x{};
        float y{};
        
        int xi() const;
        int yi() const;

        float scalar(const vec2f& v2) const;
        float cross(const vec2f& v2) const;
        float distance(const vec2f& v2) const;
        float length() const;
        vec2f& normalize(float norm = 1);
        vec2f& normalizeMin(float norm = 1);
        vec2f& normalizeMax(float norm = 1);

        vec2f copy() const;

        vec2f(float x = 0, float y = 0)
        : x{ x }, y { y }
        { }

        vec2f& operator+=(const vec2f& v2);
        vec2f& operator-=(const vec2f& v2);
        vec2f& operator*=(float val);
        vec2f& operator/=(float val);
        vec2f& operator++();        //++x
        vec2f& operator++(int);     //x++
        vec2f& operator--();
        vec2f& operator--(int);
        float operator[] (int index) const;

        operator std::string() const;
    };


    vec2f operator-(const vec2f& v1);
    bool operator!(const vec2f& v1);

    vec2f operator+(const vec2f& v1, const vec2f& v2);
    vec2f operator-(const vec2f& v1, const vec2f& v2);
    vec2f operator*(const vec2f& v, float val);
    vec2f operator*(float val, const vec2f& v);
    vec2f operator/(const vec2f& v, float val);
    vec2f operator/(float val, const vec2f& v);

    bool operator== (const vec2f& v1, const vec2f& v2);
    bool operator!= (const vec2f& v1, const vec2f& v2);
    std::ostream& operator<< (std::ostream& out, const vec2f& point);
}

#endif