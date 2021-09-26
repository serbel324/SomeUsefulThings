#pragma once
#include <cmath>

/* define NO_USINGS before #include if you don't want Vec3f, Vec2d etc to be generated */
#ifndef NO_USINGS 
#define USINGS_FOR_TYPES
#endif
#undef NO_USINGS

/* define NO_IOSTREAM before #include if your type doesn't support iostream */
#ifndef NO_IOSTREAM 
#define IOSTREAM_SUPPORTED
#endif
#undef NO_IOSTREAM

/* define FTYPE before #include to specify float type to be used */
#ifndef FTYPE 
#define FTYPE double
#endif

/* define EPS before #include to specify the epsilon value used in comparions */
#ifndef EPS
#define EPS 1e-9
#endif

template <typename T> /* T must be algebraic field */
struct Vec3
{
    Vec3(T x = 0, T y = 0, T z = 0);
    Vec3(const Vec3& other);
    Vec3(Vec3&& other);

    Vec3& operator=(const Vec3& other);
    Vec3& operator=(Vec3&& other);

    ~Vec3() = default;


    /* comparison without eps, be careful with floating types */
    bool operator==(const Vec3& other) const;
    bool operator!=(const Vec3& other) const;

    /* true if this' and other's coordinates differerence is no more than eps */
    bool compare_with_eps(const Vec3& other) const;

    Vec3 operator-() const;

    Vec3& operator+=(Vec3 r);
    Vec3& operator-=(Vec3 r);

    template <typename T1>
    Vec3& operator*=(T1 r);
    template <typename T1>
    Vec3& operator/=(T1 r);

    Vec3 operator+(Vec3 r) const;
    Vec3 operator-(Vec3 r) const;

    template <typename T1>
    Vec3 operator*(T1 r) const;
    template <typename T1>
    Vec3 operator/(T1 r) const;

    FTYPE abs();
    Vec3 norm();

    T x;
    T y;
    T z;
};

#ifdef USINGS_FOR_TYPES
using Vec3i = Vec3<int>;
using Vec3f = Vec3<float>;
using Vec3d = Vec3<double>;
#endif

/* returns scalar product */
template <typename T>
T dot_prod(Vec3<T> l, Vec3<T> r);

/* returns vector product */
template <typename T>
Vec3<T> cross_prod(Vec3<T> l, Vec3<T> r);

/* returns distance between point a and b */
template <typename T>
FTYPE dist(Vec3<T> a, Vec3<T> b);

/* returns angle between vectors a and b in range[0, pi] */
template <typename T>
FTYPE angle(Vec3<T> a, Vec3<T> b);

/* returns true if a and b are collinear */
template <typename T>
bool check_parallel(Vec3<T> a, Vec3<T> b);

#ifdef IOSTREAM_SUPPORTED
#include <iostream>
/* ------------------ I/O operators ------------------ */
template <typename T>
std::istream& operator>>(std::istream& in, Vec3<T>& v);

template <typename T>
std::ostream& operator<<(std::ostream& out, const Vec3<T>& v);
#endif

/* =========================================================================== */
/* =============================== DEFINITIONS =============================== */
/* =========================================================================== */


template<typename T>
Vec3<T>::Vec3(T x, T y, T z)
    : x(x), y(y), z(z)
{}

template<typename T>
Vec3<T>::Vec3(const Vec3& other)
    : x(other.x), y(other.y), z(other.z)
{}

template<typename T>
Vec3<T>::Vec3(Vec3&& other)
    : x(other.x), y(other.y), z(other.z)
{
    other.x = other.y = other.z = 0;
}

template<typename T>
Vec3<T>& Vec3<T>::operator=(const Vec3& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
}

template<typename T>
Vec3<T>& Vec3<T>::operator=(Vec3&& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    other.x = other.y = other.z = 0;
}

template<typename T>
bool Vec3<T>::operator==(const Vec3& other) const
{
    return (x == other.x && y == other.y && z == other.z);
}

template<typename T>
bool Vec3<T>::operator!=(const Vec3& other) const
{
    return (x != other.x || y != other.y || z != other.z);
}

template<typename T>
bool Vec3<T>::compare_with_eps(const Vec3& other) const
{
    return (
        std::abs(x - other.x) < EPS &&
        std::abs(y - other.y) < EPS &&
        std::abs(z - other.z) < EPS);
}

template<typename T>
Vec3<T> Vec3<T>::operator-() const
{
    return Vec3(-x, -y, -z);
}

template<typename T>
Vec3<T>& Vec3<T>::operator+=(Vec3 r)
{
    x += r.x;
    y += r.y;
    z += r.z;
    return *this;
}

template<typename T>
Vec3<T>& Vec3<T>::operator-=(Vec3 r)
{
    return *this += -r;
}

template<typename T>
Vec3<T> Vec3<T>::operator+(Vec3 r) const
{
    Vec3 v(*this);
    return v += r;
}

template<typename T>
Vec3<T> Vec3<T>::operator-(Vec3 r) const
{
    Vec3 v(*this);
    return v -= r;
}

template<typename T>
FTYPE Vec3<T>::abs()
{
    return std::sqrt(x * x + y * y + z * z);
}

template<typename T>
Vec3<T> Vec3<T>::norm()
{
    if (abs() < EPS)
    {
        return *this;
    }
    return Vec3(x / abs(), y / abs(), z / abs());
}

template<typename T>
template<typename T1>
Vec3<T>& Vec3<T>::operator*=(T1 r)
{
    x *= r;
    y *= r;
    return *this;
}

template<typename T>
template<typename T1>
Vec3<T>& Vec3<T>::operator/=(T1 r)
{
    return *this *= 1 / r;
}

template<typename T>
template<typename T1>
Vec3<T> Vec3<T>::operator*(T1 r) const
{
    Vec3 v(*this);
    return v *= r;
}

template<typename T>
template<typename T1>
Vec3<T> Vec3<T>::operator/(T1 r) const
{
    Vec3 v(*this);
    return v /= r;
}

template<typename T>
T dot_prod(Vec3<T> l, Vec3<T> r)
{
    return l.x * r.x + l.y * r.y + l.z * r.z;
}

template<typename T>
Vec3<T> cross_prod(Vec3<T> l, Vec3<T> r)
{
    return Vec3<T>(
        l.y * r.z - l.z * r.y,
        -l.x * r.z + l.z * r.x,
        l.x * r.y - l.y * r.x);
}

template<typename T>
FTYPE dist(Vec3<T> a, Vec3<T> b)
{
    return (a - b).abs();
}

template<typename T>
FTYPE angle(Vec3<T> a, Vec3<T> b)
{
    if (a.abs() < EPS || b.abs() < EPS)
    {
        return 0;
    }

    return std::acos(dot_prod(a, b) / a.abs() / b.abs());
}

template<typename T>
bool check_parallel(Vec3<T> a, Vec3<T> b)
{
    double aabs = a.abs();
    double babs = a.abs();

    if (aabs < EPS || babs < EPS)
    {
        return true;
    }

    return ((cross_prod(a, b) / aabs / babs).abs() < EPS);
}

#ifdef IOSTREAM_SUPPORTED
template<typename T>
std::istream& operator>>(std::istream& in, Vec3<T>& v)
{
    in >> v.x >> v.y >> v.z;
    return in;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Vec3<T>& v)
{
    out << v.x << ' ' << v.y << ' ' << v.z;
    return out;
}
#endif

#undef FTYPE
#undef USINGS_FOR_TYPES
#undef IOSTREAM_SUPPORRED
#undef EPS