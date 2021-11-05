#ifndef _PRIMITIVE_PAINTER_HPP
#define _PRIMITIVE_PAINTER_HPP

#include <SFML/OpenGL.hpp>

#include "primitives/Line.h"

class PrimitivePainter {
public:
    constexpr PrimitivePainter() noexcept = default;

    inline void PaintLine(Line2D const &line) noexcept {
        glVertex2d(line.s.x, line.s.y);
        glVertex2d(line.e.x, line.e.y);
    }
};

#endif