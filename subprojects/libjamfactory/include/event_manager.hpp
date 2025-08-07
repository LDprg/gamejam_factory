#pragma once

#include "events.hpp"
#include "events_helpers.hpp"

#include <SFML/Network/TcpSocket.hpp>
#include <functional>

template <Sendable T> struct EventCallback : std::function<void(const T &)> {
    using Base = std::function<void(const T &)>;
    using Base::Base;
};

class EventManager {
  public:
    template <Sendable T>
    sf::Socket::Status send(sf::TcpSocket &socket, T &&ev) {
        return this->send(socket, Event{ev});
    }

    sf::Socket::Status send(sf::TcpSocket &socket, Event &&ev) {
        sf::Packet packet;
        packet << ev;
        return socket.send(packet);
    }

    template <Sendable T> void dispatch(EventCallback<T> call) {
        EventCallback<Event> callback = [call](const Event &evt) {
            auto ev = std::get<T>(evt);
            return call(ev);
        };
        map.emplace(std::string(type_name_v<T>), callback);
    }

    void handle(Event &&ev) {
        auto [begin, end] = map.equal_range(ev.getTypeName());
        for (auto it = begin; it != end; ++it) {
            it->second(ev);
        }
    }

  protected:
    std::unordered_multimap<std::string, EventCallback<Event>> map;
};
