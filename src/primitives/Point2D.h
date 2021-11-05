#ifndef _POINT_2D_H
#define _POINT_2D_H

struct Point2D {
    double x, y;
    
    constexpr Point2D(double _x, double _y) noexcept : x(_x), y(_y) {}
};

#endif