#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

template<class T>
class Matrix  {
    public:
        Matrix(int width, int height) {
            this->width = width;
            this->height = height;

            list.resize(width * height);
        }

        void set(int x, int y, T value) {
            list[y * width + x] = value;
        }

        const T& get(int x, int y) const {
            return list.at(y * width + x);
        }

        int getWidth() const {
            return width;
        }

        int getHeight() const {
            return height;
        }
        
    private:
        std::vector<T> list;
        int width;
        int height;

};

#endif