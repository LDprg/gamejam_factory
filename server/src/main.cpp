#include <SFML/Network.hpp>

#include <shared.hpp>

Logger logger("Server");
sf::TcpListener listener;
sf::TcpSocket socket;

auto main() -> int {
    logger.info("Starting...");

    if (listener.listen(NETWORK_PORT) != sf::Socket::Status::Done) {
        logger.fatal("Failed to bind listener!");
    }

    logger.info("Waiting for connection...");

    if (listener.accept(socket) != sf::Socket::Status::Done) {

        logger.fatal("Failed to accept socket!");
    }

    logger.info("Connected!");

    logger.info("Stopping...");

    socket.disconnect();
    listener.close();
}
