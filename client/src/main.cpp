#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>

#include "const.hpp"

int main() {
    auto window = sf::RenderWindow(sf::VideoMode({720u, 380u}), GAME_NAME);
    window.setFramerateLimit(144);

    auto circle = sf::CircleShape();
    circle.setRadius(10.f);
    circle.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();

        window.draw(circle);

        window.display();
    }
}
