#ifndef VEC_HPP
#define VEC_HPP

template <typename T>
class vec2
{
    public:
        T x;
        T y;

        vec2(T x, T y): x(x), y(y) {}
};

template <> class vec2<float>;

#endif // VEC_HPP
