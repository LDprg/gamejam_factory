#include "event_manager.hpp"
#include "events.hpp"
#include "pch/pch.hpp"
#include "threadpool.hpp"

#include <SFML/Network/Packet.hpp>
#include <SFML/Network/Socket.hpp>
#include <memory>
#include <shared.hpp>

std::shared_ptr<Logger> logger = std::make_shared<Logger>("Client");

sf::IpAddress address = sf::IpAddress::LocalHost;
sf::TcpSocket socket;

EventManager evt_mgr(logger);

// ERROR: currently not working
// Threadpool thr_pool;

void network() {
    sf::Socket::Status status = socket.connect(address, NETWORK_PORT);

    if (status != sf::Socket::Status::Done) {
        logger->fatal("Couldn't connect to Server!");
    }

    evt_mgr.send(socket, EventPlayerConnected{"Player1"});
    evt_mgr.send(socket, EventPlayerReady{});
}

int main() {
    logger->info("Staring...");
    std::thread networkThread(network);

    auto window = sf::RenderWindow(sf::VideoMode({720u, 380u}), GAME_NAME);
    window.setFramerateLimit(144);

    auto circle = sf::CircleShape();
    circle.setRadius(10.f);
    circle.setFillColor(sf::Color::Green);

    logger->info("Waiting for connection...");

    networkThread.join();
    
    logger->info("Connected!");

    logger->info("Running...");

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
    logger->info("Stopping...");
}
