#pragma once

class Logger {
  public:
    Logger(const std::string &name);

    template <typename... Args>
    void fatal(spdlog::format_string_t<Args...> fmt, Args &&...args) {
        this->logger->critical(fmt, args...);
        this->logger->critical("Fatal error! Exiting...");
        std::exit(EXIT_FAILURE);
    }

    template <typename... Args>
    void critical(spdlog::format_string_t<Args...> fmt, Args &&...args) {
        this->logger->critical(fmt, args...);
        std::exit(EXIT_FAILURE);
    }

    template <typename... Args>
    void err(spdlog::format_string_t<Args...> fmt, Args &&...args) {
        this->logger->error(fmt, args...);
    }

    template <typename... Args>
    void warn(spdlog::format_string_t<Args...> fmt, Args &&...args) {
        this->logger->warn(fmt, args...);
    }

    template <typename... Args>
    void info(spdlog::format_string_t<Args...> fmt, Args &&...args) {
        this->logger->info(fmt, args...);
    }

    template <typename... Args>
    void trace(spdlog::format_string_t<Args...> fmt, Args &&...args) {
        this->logger->trace(fmt, args...);
    }

  protected:
    std::shared_ptr<spdlog::logger> logger;
};
