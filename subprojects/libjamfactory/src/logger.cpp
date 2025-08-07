#include "../../pch/pch.hpp"

#include "logger.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

Logger::Logger(const char *name) {
    this->logger = spdlog::stdout_color_mt(name);
}
