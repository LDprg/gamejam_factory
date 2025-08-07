#include "event_manager.hpp"
#include "events.hpp"
#include "pch/pch.hpp"

#include <shared.hpp>
#include <variant>

Logger logger("Server");
sf::TcpListener listener;
sf::TcpSocket socket;

int main() {
    logger.info("Starting...");

    if (listener.listen(NETWORK_PORT) != sf::Socket::Status::Done) {
        logger.fatal("Failed to bind listener!");
    }

    logger.info("Waiting for connection...");
    if (listener.accept(socket) != sf::Socket::Status::Done) {
        logger.fatal("Failed to accept socket!");
    }

    logger.info("Connected!");

    sf::Packet packet;
    sf::Socket::Status status = socket.receive(packet);
    // EventManager evt_mgr;
    //
    // evt_mgr.dispatch<EventPlayerConnected>([](const auto &ev) {
    //     logger.warn("Player \"{}\" connected!", ev.name);
    // });
    //
    // evt_mgr.dispatch<EventPlayerReady>(
    //     [](const auto &) { logger.warn("Player ready!"); });

    while (status != sf::Socket::Status::Disconnected) {
        if (status == sf::Socket::Status::Error) {
            logger.err("Socket error!");
        }

        Event ev;
        packet >> ev;

        std::visit(overloaded{
                       [](EventPlayerConnected ev) {
                           logger.warn("Player \"{}\" connected!", ev.name);
                       },
                       [](EventPlayerReady) { logger.warn("Player ready!"); },
                       [](EventPlayerDisconncted) {
                           logger.warn("Player disconnect!");
                       },
                   },
                   ev);
        // evt_mgr.handle(std::move(ev));

        status = socket.receive(packet);
    }

    logger.info("Stopping...");

    socket.disconnect();
    listener.close();
}
