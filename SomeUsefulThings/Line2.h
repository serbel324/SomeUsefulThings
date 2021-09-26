#pragma once

#include "Vec2.h"


/* define FTYPE before #include to specify float type to be used */
#ifndef FTYPE 
#define FTYPE double
#endif

/* define EPS before #include to specify the epsilon value used in comparions */
#ifndef EPS
#define EPS 1e-9
#endif

#define VEC2F Vec2<FTYPE>

/* Line is defined by linear equation a*x + b*y + c = 0 */
struct Line2
{
    Line2();
    Line2(FTYPE a, FTYPE b, FTYPE c, bool normilize = 0);
    Line2(VEC2F p1, VEC2F p2, bool normilize = 0);
    Line2(const Line2&) = default;

    Line2(Line2&& other) noexcept;
    Line2& operator=(const Line2& other);
    Line2& operator=(Line2&& other) noexcept;

    ~Line2() = default;

    /* reduce to cos(t) * x + sin(t) * y + p = 0 */
    void normalize();
    VEC2F get_normal();

    /* calculate linear expression for vector p */
    FTYPE operator()(VEC2F p);

    FTYPE a;
    FTYPE b; 
    FTYPE c;
};

FTYPE dist(VEC2F p, Line2 l);
FTYPE dist(Line2 l, VEC2F p);
VEC2F reflect(Line2 l, VEC2F p);

/* ------------------- I/O operators ------------------- */
#include <iostream>

std::istream& operator>>(std::istream& in, Line2& l);
std::ostream& operator<<(std::ostream& out, const Line2& l);

Line2::Line2()
    : a(0), b(0), c(0)
{}

Line2::Line2(FTYPE a, FTYPE b, FTYPE c, bool normilize)
    : a(a), b(b), c(c)
{
    if (normilize)
    {
        this->normalize();
    }
}

Line2::Line2(VEC2F p1, VEC2F p2, bool normilize)
{
    VEC2F dir = p2 - p1;
    VEC2F n(dir.y, -dir.x);
    a = n.x;
    b = n.y;
    c = -a * p1.x - b * p1.y;

    if (normilize)
    {
        this->normalize();
    }
}

Line2::Line2(Line2&& other) noexcept
    : a(other.a), b(other.b), c(other.c)
{
    other.a = other.b = other.c = 0;
}


Line2& Line2::operator=(const Line2& other)
{
    a = other.a;
    b = other.b;
    c = other.c;

    return *this;
}

Line2& Line2::operator=(Line2&& other) noexcept
{
    a = other.a;
    b = other.b;
    c = other.c;
    other.a = other.b = other.c = 0;

    return *this;
}

void Line2::normalize()
{
    FTYPE d = get_normal().abs();

    if (d < EPS)
    {
        return; /* (a, b) == (0, 0) */
    }

    a /= d;
    b /= d;
    c /= d;
}

VEC2F Line2::get_normal()
{
    return VEC2F(a, b);
}

FTYPE Line2::operator()(VEC2F p)
{
    return a * p.x + b * p.y + c;
}

FTYPE dist(VEC2F p, Line2 l)
{
    return l(p) / l.get_normal().abs();
}

FTYPE dist(Line2 l, VEC2F p)
{
    return dist(p, l);
}

VEC2F reflect(Line2 l, VEC2F p)
{
    return p - (l.get_normal().norm() * dist(l, p) * 2);
}

std::istream& operator>>(std::istream& in, Line2& l)
{
    in >> l.a >> l.b >> l.c;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Line2& l)
{
    if (l.a < 0)
    {
        out << '-';
    }

    if (std::abs(l.a) != 1)
    {
        out << std::abs(l.a);
    }
    out << 'x';


    if (l.b < 0)
    {
        out << " - ";
    }
    else
    {
        out << " + ";
    }

    if (std::abs(l.b) != 1)
    {
        out << std::abs(l.b);
    }
    out << 'y';

    if (l.c != 0)
    {
        if (l.c < 0)
        {
            out << " - ";
        }
        else
        {
            out << " + ";
        }

        out << std::abs(l.c);
    }
    out << " = 0";
    return out;
}




#undef FTYPE
#undef VEC2F
#undef EPS