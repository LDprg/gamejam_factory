#include "logger.hpp"
#include <shared.hpp>

Logger logger("Server");

auto main() -> int {
    logger.info("Starting...");

    logger.info("Stopping...");
}
