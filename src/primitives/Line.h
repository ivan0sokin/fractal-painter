#ifndef _LINE_2D_H
#define _LINE_2D_H

#include <cmath>

#include "Point2D.h"

struct Line2D {
    Point2D s, e;
    
    constexpr Line2D(Point2D const &start, Point2D const &end) noexcept : s(start), e(end) {}
    constexpr Line2D(double x1, double y1, double x2, double y2) noexcept : s(Point2D(x1, y1)), e(Point2D(x2, y2)) {}

    inline Point2D Rotate(double angle) noexcept {
        double dx = e.x - s.x;
        double dy = e.y - s.y;

        double dx1 = dx * cos(angle) - dy * sin(angle);
        double dy1 = dx * sin(angle) + dy * cos(angle);

        return Point2D(s.x + dx1, s.y + dy1);
    }
};

#endif