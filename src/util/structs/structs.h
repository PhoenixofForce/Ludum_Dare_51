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
};

#endif