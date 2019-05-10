#ifndef VEC_HPP
#define VEC_HPP

template <typename T>
class vec2
{
    public:
        T x;
        T y;

        vec2(T x = 0, T y = 0): x(x), y(y) {}

        T getX() {return x;}
        T getY() {return y;}
};

template <typename T>
class vec3
{
    public:
        T x;
        T y;
        T z;

        vec3(T x = 0, T y = 0, T z = 0): x(x), y(y), z(z) {}
};

#endif // VEC_HPP
