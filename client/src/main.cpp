#include "event_manager.hpp"
#include "events.hpp"
#include "pch/pch.hpp"

#include <SFML/Network/Packet.hpp>
#include <SFML/Network/Socket.hpp>
#include <shared.hpp>

Logger logger("Client");

sf::IpAddress address = sf::IpAddress::LocalHost;
sf::TcpSocket socket;

int main() {
    logger.info("Staring...");

    auto window = sf::RenderWindow(sf::VideoMode({720u, 380u}), GAME_NAME);
    window.setFramerateLimit(144);

    auto circle = sf::CircleShape();
    circle.setRadius(10.f);
    circle.setFillColor(sf::Color::Green);

    logger.info("Connecting...");

    sf::Socket::Status status = socket.connect(address, NETWORK_PORT);

    EventManager evt_mgr;

    if (status != sf::Socket::Status::Done) {
        logger.fatal("Couldn't connect to Server!");
    }

    status = evt_mgr.send(socket, EventPlayerConnected{"Player1"});
    if (status != sf::Socket::Status::Done) {
        logger.fatal("Error registering to server!");
    }

    status = evt_mgr.send(socket, EventPlayerReady{});
    if (status != sf::Socket::Status::Done) {
        logger.fatal("Error registering to server!");
    }

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
        window.close();
    }
    logger.info("Stopping...");
}
