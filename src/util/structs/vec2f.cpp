#include "vec2f.h"

namespace vec {

    int vec2f::xi() const {
        return (int) x;
    }   
    
    int vec2f::yi() const {
        return (int) y;
    }

    float vec2f::scalar(const vec2f& v2) const {
        return v2.x * x + v2.y * y;
    }

    float vec2f::cross(const vec2f& v2) const {
        return x + v2.y - y * v2.x;;
    }

    float vec2f::distance(const vec2f& v2) const{
        float dx = x - v2.x;
        float dy = y - v2.y;
        return sqrt(dx * dx + dy * dy);
    }
    
    float vec2f::length() const {
        return std::sqrt(x * x + y * y);
    }

    vec2f& vec2f::normalize(float norm) {
        float length = this->length();
        if(length != 0) {
            *this /= length;
        } else {
            x = 0;
            y = 0;
        }

        *this *= norm;
        return *this;  
    }

    vec2f& vec2f::normalizeMin(float norm) {
        float length = this->length();
        if(length > norm) return normalize(norm);
        return *this;
    }

    vec2f& vec2f::normalizeMax(float norm) {
        float length = this->length();
        if(length < norm) return normalize(norm);
        return *this;
    }

    vec2f vec2f::copy() const {
        return vec2f{*this};
    }

    vec2f& vec2f::operator-=(const vec2f& v2) {
        x -= v2.x;
        y -= v2.y;
        return *this;
    }

    bool operator!(const vec2f& v) {
        return !v.length();
    }

    vec2f& vec2f::operator*=(float val) {
        x *= val;
        y *= val;
        return *this;
    }

    vec2f& vec2f::operator/=(float val) {
        x /= val;
        y /= val;
        return *this;
    }

    vec2f& vec2f::operator+=(const vec2f& v2) {
        x += v2.x;
        y += v2.y;
        return *this;
    }

    vec2f& vec2f::operator++() {
        x += 1;
        return *this;
    }

    vec2f& vec2f::operator++(int) {
        y += 1;
        return *this;
    }

    vec2f& vec2f::operator--() {
        x -= 1;
        return *this;
    }

    vec2f& vec2f::operator--(int)  {
        y -= 1;
        return *this;
    }

    float vec2f::operator[] (int index) const {
        assert(index == 0 || index == 1);

        if(index == 0) return x;
        if(index == 1) return y;
        return 0;
    }

    vec2f::operator std::string() const {
        std::string out{"(" + std::to_string(x) + " | " + std::to_string(y) + ")"};
        return out;
    }

    vec2f operator-(const vec2f& v1) {
        return vec2f{ - v1.x, -v1.y};
    }

    vec2f operator+(const vec2f& v1, const vec2f& v2) {
        return vec2f{v1.x + v2.x, v1.y + v2.y};
    }

    vec2f operator-(const vec2f& v1, const vec2f& v2) {
        return vec2f{v1.x - v2.x, v1.y - v2.y};
    }

    vec2f operator*(const vec2f& v, float val) {
        return vec2f{v.x * val, v.y * val};
    }

    vec2f operator*(float val, const vec2f& v) {
        return v * val;
    }

    vec2f operator/(const vec2f& v, float val) {
        return vec2f{v.x / val, v.y / val};
    }

    vec2f operator/(float val, const vec2f& v) {
        return v / val;
    }

    bool operator== (const vec2f& v1, const vec2f& v2) {
        return v1.x == v2.x && v1.y == v2.y;
    }

    bool operator!= (const vec2f& v1, const vec2f& v2) {
        return !(v1 == v2);
    }

    std::ostream& operator<< (std::ostream& out, const vec2f& point) {
        out << "(" << point.x << " | " << point.y << ")";
        return out;
    }

}
