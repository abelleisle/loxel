#ifndef VEC_HPP
#define VEC_HPP

template <typename T>
class vec2
{
    public:
        T x;
        T y;

        vec2(T x = 0, T y = 0): x(x), y(y) {}
};

#endif // VEC_HPP
