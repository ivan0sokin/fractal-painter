#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <FractalPainter.hpp>

#include <numbers>
#include <iostream>

int main() {
    const int windowWidth = 900, windowHeight = 900;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Hello, fractals!");

    const double unit = 10.0;
    const double theta = std::numbers::pi / 3;
    auto kochSnowflake = FractalPainter(windowWidth, windowHeight, unit, theta);

    try {
        kochSnowflake.SetPrimaryPattern("F++F++F");
        kochSnowflake.SetSecondaryPattern("F-F++F-F");
    } catch (std::exception &e) {
        std::cout << e.what() << '\n';
        return -1;
    }

    kochSnowflake.SetColor(Color(0.0, 0.0, 1.0));

    const auto startingPosition = Point2D(450, 450);
    const double startingAngle = 0.0;
    const size_t generationNumber = 3;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color(255, 255, 255, 255));
        kochSnowflake.Paint(startingPosition, startingAngle, generationNumber - 1);
        window.display();
    }

    return 0;
}