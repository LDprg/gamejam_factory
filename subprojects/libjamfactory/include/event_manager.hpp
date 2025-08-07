#pragma once

#include "events.hpp"
#include "events_helpers.hpp"
#include "logger.hpp"

#include <SFML/Network/TcpSocket.hpp>
#include <functional>
#include <memory>
#include <mutex>

template <Sendable T> struct EventCallback : std::function<void(const T &)> {
    using Base = std::function<void(const T &)>;
    using Base::Base;
};

class EventManager {
  public:
    EventManager(std::shared_ptr<Logger> logger) : logger(logger) {}

    template <Sendable T>
    sf::Socket::Status send(sf::TcpSocket &socket, T &&ev) {
        return this->send(socket, Event{ev});
    }

    sf::Socket::Status send(sf::TcpSocket &socket, Event &&ev) {
        sf::Packet packet;
        packet << ev;
        auto status = socket.send(packet);

        if (status != sf::Socket::Status::Done) {
            logger->err("Error sending event to server!");
        }

        return status;
    }

    template <Sendable T> void dispatch(EventCallback<T> call) {
        EventCallback<Event> callback = [call](const Event &evt) {
            auto ev = std::get<T>(evt);
            return call(ev);
        };

        std::lock_guard<std::mutex> lock(map_mux);
        map.emplace(std::string(type_name_v<T>), callback);
    }

    void handle(Event &&ev) {
        std::lock_guard<std::mutex> lock(map_mux);
        auto [begin, end] = map.equal_range(ev.getTypeName());
        for (auto it = begin; it != end; ++it) {
            it->second(ev);
        }
    }

  protected:
    std::unordered_multimap<std::string, EventCallback<Event>> map;
    std::mutex map_mux;
    std::shared_ptr<Logger> logger;
};
