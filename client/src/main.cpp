#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <spdlog/spdlog.h>

#include <shared.hpp>

Logger logger("Client");

sf::IpAddress address = sf::IpAddress::LocalHost;
sf::TcpSocket socket;

auto main() -> int {
    logger.info("Staring...");

    auto window = sf::RenderWindow(sf::VideoMode({720u, 380u}), GAME_NAME);
    window.setFramerateLimit(144);

    auto circle = sf::CircleShape();
    circle.setRadius(10.f);
    circle.setFillColor(sf::Color::Green);

    logger.info("Connecting...");

    sf::Socket::Status status = socket.connect(address, NETWORK_PORT);

    logger.info("Running...");

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
    logger.info("Stopping...");
}
