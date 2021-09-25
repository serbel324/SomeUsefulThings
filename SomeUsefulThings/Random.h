#pragma once

#include <ctime>
#include <random>

double get_random_double(double a, double b)
{
    if (b <= a) 
    {
        return 0;
    }

    static std::mt19937_64 randomizer(std::time(0));
    long double base = randomizer(); /* in range [0; 9981545732273789042) */
    long double maxr = 9981545732273789042.;
    long double normilized = base / maxr; /* in range [0; 9981545732273789042) */
    return normilized * (b - a) + a;
}

int get_random_int(int a, int b)
{
    if (b <= a) 
    {
        return 0;
    }

    static std::mt19937_64 randomizer(std::time(0));
    unsigned long long base = randomizer(); /* in range [0; 9981545732273789042) */
    long long normilized = base % (b - a);
    return normilized + a;
}
