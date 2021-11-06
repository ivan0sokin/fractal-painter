#ifndef _FRACTAL_PAINTER_HPP
#define _FRACTAL_PAINTER_HPP

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

#include "PrimitivePainter.hpp"
#include "Rule.hpp"

class FractalPainter {
public:
    constexpr FractalPainter() = delete;
    constexpr FractalPainter(FractalPainter const &other) = delete;
    constexpr FractalPainter(FractalPainter &&other) = delete;

    inline FractalPainter(long windowWidth, long windowHeight, double unit, double angle, double theta) noexcept : 
        windowWidth(windowWidth), windowHeight(windowHeight), unit(unit), angle(angle), theta(theta) {}

    inline void SetInitiatingRule(std::initializer_list<Rule> const &rules) noexcept { 
        initiatingRules.assign(rules);
    }

    inline void SetProducitonRule(std::initializer_list<Rule> const &rules) noexcept { 
        productionRules.assign(rules);
    }

    inline void Paint(Point2D startingPosition, double startingAngle, size_t iterationCount = 1) noexcept {
        position = startingPosition;
        angle = startingAngle;
        
        glBegin(GL_LINES);

        for (auto const &initiatingRule : initiatingRules) {
            switch (initiatingRule)
            {
            case Rule::Forward:
                DoProductionRule(iterationCount);
                break;
            case Rule::Plus:
                angle += theta;
                break;
            case Rule::Minus:
                angle -= theta;
                break;
            default:
                break;
            }
        }

        glEnd();
    }
private:
    inline void DoProductionRule(size_t iterationCount) noexcept {
        for (auto const &produtcionRule : productionRules) {
            switch (produtcionRule)
            {
            case Rule::Forward:
                if (iterationCount == 0) {
                    auto line = Line2D(position, Point2D(position.x + unit, position.y));
                    Point2D rotated = line.Rotate(angle);

                    auto translated_line = Line2D(TranslatePoint(line.s), TranslatePoint(rotated));
                    painter.PaintLine(translated_line);

                    position = rotated;
                    break;
                }

                DoProductionRule(iterationCount - 1);

                break;
            case Rule::Plus:
                angle += theta;
                break;
            case Rule::Minus:
                angle -= theta;
                break;
            default:
                break;
            }
        }
    }

    constexpr Point2D TranslatePoint(Point2D p) noexcept {
        double x = p.x / static_cast<double>(windowWidth) * (xMax - xMin) + xMin;
        double y = p.y / static_cast<double>(windowHeight) * (yMax - yMin) + yMin;

        return Point2D(x, y);
    }
private:
    long windowWidth = 0, windowHeight = 0;

    double unit = 10.0;
    double angle = 0.0;
    double theta = 0.0;

    std::vector<Rule> initiatingRules;
    std::vector<Rule> productionRules;

    PrimitivePainter painter;
    
    Point2D position = { 0, 0 };

    constexpr static double xMax = 1.0, xMin = -1.0, yMax = 1.0, yMin = -1.0;
};

#endif