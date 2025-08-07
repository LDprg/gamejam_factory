#include "event_manager.hpp"
#include "events.hpp"
#include "pch/pch.hpp"

#include <shared.hpp>

std::shared_ptr<Logger> logger = std::make_shared<Logger>("Server");
EventManager evt_mgr(logger);

sf::TcpSocket socket;

void listener() {
    sf::TcpListener listener;

    if (listener.listen(NETWORK_PORT) != sf::Socket::Status::Done) {
        logger->fatal("Failed to bind listener!");
    }

    logger->info("Waiting for connection...");

    if (listener.accept(socket) != sf::Socket::Status::Done) {
        logger->fatal("Failed to accept socket!");
    }
}

int main() {
    logger->info("Starting...");
    std::thread listenerThread(listener);

    evt_mgr.dispatch<EventPlayerConnected>([](const auto &ev) {
        logger->warn("Player \"{}\" connected!", ev.name);
    });

    evt_mgr.dispatch<EventPlayerReady>(
        [](const auto &) { logger->warn("Player ready!"); });

    listenerThread.join();

    logger->info("Connected!");

    sf::Packet packet;
    sf::Socket::Status status = socket.receive(packet);

    while (status != sf::Socket::Status::Disconnected) {
        if (status == sf::Socket::Status::Error) {
            logger->err("Socket error!");
        }

        Event ev;
        packet >> ev;

        evt_mgr.handle(std::move(ev));

        status = socket.receive(packet);
    }

    logger->info("Stopping...");
}
