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

    sf::Packet packet;
    sf::Socket::Status status = socket.receive(packet);
    while (status != sf::Socket::Status::Disconnected) {
        if (status == sf::Socket::Status::Error) {
            logger.err("Socket error!");
        }

        status = socket.receive(packet);
    }

    logger.info("Stopping...");

    socket.disconnect();
    listener.close();
}
