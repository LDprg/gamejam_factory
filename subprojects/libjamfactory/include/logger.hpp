#pragma once

#include <spdlog/spdlog.h>

class Logger {
  public:
    Logger(const char *name);

    template <typename... Args>
    void fatal(fmt::format_string<Args...> fmt, Args &&...args) {
        this->logger->critical(fmt, args...);
        this->logger->critical("Fatal error! Exiting...");
        std::exit(EXIT_FAILURE);
    }

    template <typename... Args>
    void critical(fmt::format_string<Args...> fmt, Args &&...args) {
        this->logger->critical(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void err(fmt::format_string<Args...> fmt, Args &&...args) {
        this->logger->error(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void warn(fmt::format_string<Args...> fmt, Args &&...args) {
        this->logger->warn(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void info(fmt::format_string<Args...> fmt, Args &&...args) {
        this->logger->info(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void trace(fmt::format_string<Args...> fmt, Args &&...args) {
        this->logger->trace(fmt, std::forward<Args>(args)...);
    }

  protected:
    std::shared_ptr<spdlog::logger> logger;
};
