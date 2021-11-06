#ifndef _PRIMITIVE_PAINTER_HPP
#define _PRIMITIVE_PAINTER_HPP

#include <SFML/OpenGL.hpp>

#include "primitives/Line.h"
#include "Color.h"

class PrimitivePainter {
public:
    inline PrimitivePainter() noexcept = default;

    inline void SetColor(Color const &color) {
        this->color = color;
    }

    inline void PaintLine(Line2D const &line) noexcept {
        glColor4d(color.r, color.g, color.b, color.a);
        glVertex2d(line.s.x, line.s.y);
        glVertex2d(line.e.x, line.e.y);
    }
private:
    Color color = { 0, 0, 0, 1 };
};

#endif