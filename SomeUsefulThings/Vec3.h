#pragma once
#include <cmath>

#define USINGS_FOR_TYPES
#define IOSTREAM_SUPPORTED

using __ftype = double;

template <typename T> // T must be algebraic field
struct Vec3
{
    Vec3(T x = 0, T y = 0, T z = 0)
        : x(x), y(y), z(z)
    {}
    Vec3(const Vec3& other)
        : x(other.x), y(other.y), z(other.z)
    {}
    Vec3(Vec3&& other)
        : x(other.x), y(other.y), z(other.z)
    {
        other.x = 0;
        other.y = 0;
        other.z = 0;
    }


    Vec3& operator=(const Vec3& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
    }

    Vec3& operator=(Vec3&& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        other.x = 0;
        other.y = 0;
        other.z = 0;
    }

    ~Vec3() = default;

    Vec3 operator-() const
    {
        return Vec3(-x, -y, -z);
    }

    Vec3& operator+=(Vec3 r)
    {
        x += r.x;
        y += r.y;
        z += r.z;
        return *this;
    }

    Vec3& operator-=(Vec3 r)
    {
        return *this += -r;
    }

    Vec3& operator+(Vec3 r) const
    {
        Vec3 v(*this);
        return v += r;
    }

    Vec3& operator-(Vec3 r) const
    {
        Vec3 v(*this);
        return v -= r;
    }

    __ftype abs()
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    T x;
    T y;
    T z;
};

#ifdef USINGS_FOR_TYPES
using Vec3i = Vec3<int>;
using Vec3f = Vec3<float>;
using Vec3d = Vec3<double>;
#endif


template <typename T>
T dot_prod(Vec3<T> l, Vec3<T> r) /* returns scalar product */
{
    return l.x * r.x + l.y * r.y + l.z * r.z;
}

template <typename T>
Vec3<T> cross_prod(Vec3<T> l, Vec3<T> r) /* returns vector product */
{
    return Vec3(
        l.y * r.z - l.z * r.y,
        -l.x * r.z + l.z * r.x,
        l.x * r.y - l.y * r.x);
}

template <typename T>
__ftype dist(Vec3<T> a, Vec3<T> b) /* returns distance between point a and b */
{
    return (a - b).abs();
}

template <typename T>
__ftype angle(Vec3<T> a, Vec3<T> b) /* returns angle between vectors aand b int range[-pi, pi] */
{
    return std::atan2(cross_prod(a, b), dot_prod(a, b));
}
 
#ifdef IOSTREAM_SUPPORTED
#include <iostream>

/* ------------------ I/O operators ------------------ */
template <typename T>
std::istream& operator>>(std::istream& in, Vec3<T>& v)
{
    in >> v.x >> v.y >> v.z;
    return in;
}

template <typename T>
std::ostream& operator<<(std::ostream& in, Vec3<T>& v)
{
    out << v.x << ' ' << v.y << ' ' << v.z;
    return in;
}
#endif