#include "Vec2.h"
#include "Vec3.h"
#include "Line2.h"

#include <iostream>

int main()
{
    Vec2d o(0, 0);
    Vec2d a(1, 1);
    Vec2d p(10, 10);

    Line2 l(o, a);

    std::cout << l << std::endl;
    std::cout << l(p) << std::endl;

    std::cout << l.get_normal() << std::endl;
    std::cout << reflect(l, p) << std::endl;
}