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
    
    /* comparison without eps, be careful with floating types */
    bool operator==(const Vec2& other) const
    {
        return (x == other.x && y == other.y);
    }

    /* comparison without eps, be careful with floating types */
    bool operator!=(const Vec2& other) const
    {
        return (x != other.x || y != other.y);
    }

    /* true if this' and other's coordinates differerence is no more than eps */
    bool compare_with_eps(const Vec2& other) const
    {
        return (std::abs(x - other.x) < EPS && std::abs(y - other.y) < EPS);
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
        other.x = other.y = 0;
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

    template <typename T1>
    Vec2& operator*=(T1 r)
    {
        x *= r;
        y *= r;
        return *this;
    }

    template <typename T1>
    Vec2& operator/=(T1 r)
    {
        return *this *= 1 / r;
    }

    Vec2 operator+(Vec2 r) const
    {
        Vec2 v(*this);
        return v += r;
    }

    Vec2 operator-(Vec2 r) const
    {
        Vec2 v(*this);
        return v -= r;
    }

    template <typename T1>
    Vec2 operator*(T1 r) const
    {
        Vec2 v(*this);
        return v *= r;
    }

    template <typename T1>
    Vec2 operator/(T1 r) const
    {
        Vec2 v(*this);
        return v /= r;
    }

    FTYPE abs()
    {
        return std::sqrt(x * x + y * y);
    }

    Vec2 norm()
    {
        if (abs() < EPS)
        {
            return *this;
        }
        return Vec2(x / abs(), y / abs());
    }

    T x;
    T y;
};

#ifdef USINGS_FOR_TYPES
using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;
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
FTYPE dist(Vec2<T> a, Vec2<T> b) /* returns distance between point a and b */
{
    return (a - b).abs();
}

template <typename T>
FTYPE angle(Vec2<T> a, Vec2<T> b) /* returns angle between vectors a and b in range[-pi, pi] */
{
    return std::atan2(cross_prod(a, b), dot_prod(a, b));
}

template <typename T>
bool check_parallel(Vec2<T> a, Vec2<T> b) /* returns true if a and b are collinear */
{
    double aabs = a.abs();
    double babs = a.abs();

    if (aabs < EPS || babs < EPS)
    {
        return true;
    }

    return (std::abs(cross_prod(a, b) / aabs / babs) < EPS);
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
std::ostream& operator<<(std::ostream& out, const Vec2<T>& v)
{
    out << v.x << ' ' << v.y;
    return out;
}
#endif

#undef FTYPE
#undef USINGS_FOR_TYPES
#undef IOSTREAM_SUPPORRED
#undef EPS