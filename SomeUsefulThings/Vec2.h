#pragma once
#include <cmath>

#define USINGS_FOR_TYPES
#define IOSTREAM_SUPPORTED

using __ftype = double;

template <typename T> /* T must be algebraic field */
struct Vec2
{
    Vec2(T x = 0, T y = 0)
        : x(x), y(y)
    {}
    Vec2(const Vec2& other)
        : x(other.x), y(other.y)
    {}
    Vec2(Vec2&& other)
        : x(other.x), y(other.y)
    {
        other.x = 0;
        other.y = 0;
    }


    Vec2& operator=(const Vec2& other)
    {
        x = other.x;
        y = other.y;
    }

    Vec2& operator=(Vec2&& other)
    {
        x = other.x;
        y = other.y;
        other.x = 0;
        other.y = 0;
    }

    ~Vec2() = default;

    Vec2 operator-() const
    {
        return Vec2(-x, -y);
    }

    Vec2& operator+=(Vec2 r)
    {
        x += r.x;
        y += r.y;
        return *this;
    }

    Vec2& operator-=(Vec2 r)
    {
        return *this += -r;
    }

    Vec2& operator+(Vec2 r) const
    {
        Vec2 v(*this);
        return v += r;
    }

    Vec2& operator-(Vec2 r) const
    {
        Vec2 v(*this);
        return v -= r;
    }

    __ftype abs()
    {
        return std::sqrt(x * x + y * y);
    }

    T x;
    T y;
};

#ifdef USINGS_FOR_TYPES
using Vec3i = Vec2<int>;
using Vec3f = Vec2<float>;
using Vec3d = Vec2<double>;
#endif


template <typename T>
T dot_prod(Vec2<T> l, Vec2<T> r) /* returns scalar product */
{
    return l.x * r.x + l.y * r.y;
}

template <typename T>
T cross_prod(Vec2<T> l, Vec2<T> r) /* returns vector product = |x|*|y|*sin(angle(x,y)) */
{
    return l.x * r.y - l.y * r.x;
}

template <typename T>
__ftype dist(Vec2<T> a, Vec2<T> b) /* returns distance between point a and b */
{
    return (a - b).abs();
}

template <typename T>
__ftype angle(Vec2<T> a, Vec2<T> b) /* returns angle between vectors a and b in range[-pi, pi] */
{
    return std::atan2(cross_prod(a, b), dot_prod(a, b));
}

#ifdef IOSTREAM_SUPPORTED
#include <iostream>

/* ------------------ I/O operators ------------------ */
template <typename T>
std::istream& operator>>(std::istream& in, Vec2<T>& v)
{
    in >> v.x >> v.y;
    return in;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, Vec2<T>& v)
{
    out << v.x << ' ' << v.y;
    return out;
}
#endif