#ifndef _COLOR_H
#define _COLOR_H

struct Color {
    double r, g, b, a;

    constexpr Color(double r, double g, double b, double a = 1.0) noexcept : r(r), g(g), b(b), a(a) {}
};

#endif