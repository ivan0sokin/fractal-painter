#ifndef _FRACTAL_PAINTER_HPP
#define _FRACTAL_PAINTER_HPP

#include <memory>
#include <stack>

#include "PatternParser.hpp"
#include "PrimitivePainter.hpp"

class FractalPainter {
public:
    constexpr FractalPainter() = delete;
    constexpr FractalPainter(FractalPainter const &other) = delete;
    constexpr FractalPainter(FractalPainter &&other) = delete;

    inline FractalPainter(long windowWidth, long windowHeight, double unit, double angle, double theta) noexcept : 
        windowWidth(windowWidth), windowHeight(windowHeight), unit(unit), angle(angle), theta(theta) {}

    inline void SetPrimaryPattern(std::string_view primaryPattern) { 
        auto parser = PatternParser(primaryPattern);
        initiatingRules = parser.Parse();
    }

    inline void SetSecondaryPattern(std::string_view secondaryPattern) {
        auto parser = PatternParser(secondaryPattern);
        productionRules = parser.Parse();
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
            default:
                ParseSecondaryRule(initiatingRule);
                break;
            }
        }

        glEnd();
    }
private:
    inline void DoProductionRule(size_t iterationCount) noexcept {
        for (auto const &productionRule : productionRules) {
            switch (productionRule)
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
            default:
                ParseSecondaryRule(productionRule);
                break;
            }
        }
    }

    inline void ParseSecondaryRule(Rule const &rule) noexcept {
        switch (rule)
        {
        case Rule::Plus:
            angle += theta;
            break;
        case Rule::Minus:
            angle -= theta;
            break;
        case Rule::Save:
            savedPositions.push(position);
            savedAngles.push(angle);
            break;
        case Rule::Restore:
            position = savedPositions.top();
            angle = savedAngles.top();

            savedPositions.pop();
            savedAngles.pop();
        default:
            break;
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

    std::stack<Point2D> savedPositions;
    std::stack<double> savedAngles;

    constexpr static double xMax = 1.0, xMin = -1.0, yMax = 1.0, yMin = -1.0;
};

#endif