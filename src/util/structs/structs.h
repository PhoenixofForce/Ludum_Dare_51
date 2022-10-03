#ifndef STRUCTS_H
#define STRUCTS_H

struct Color {
    int r{};
    int g{};
    int b{};
    int a{ 255 };
};

struct Rect {
    int x{0};
    int y{0};
    int w{1};
    int h{1};

    bool intersects(const Rect& r2) {
        return !(
            r2.x > x + w ||
            r2.x + r2.w < x ||
            r2.y > y + h ||
            r2.y + r2.h < y
        );
    }

    bool intersects(const int& x, const int& y) {
        return intersects(Rect{x, y, 1, 1});
    }
};

#endif