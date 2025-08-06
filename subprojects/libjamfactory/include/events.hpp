#pragma once

#include "events_helpers.hpp"

struct EventPlayerConnected {
    std::string name;
};

inline sf::Packet &operator<<(sf::Packet &packet,
                              const EventPlayerConnected &m) {
    return packet << m.name;
}

inline sf::Packet &operator>>(sf::Packet &packet, EventPlayerConnected &m) {
    return packet >> m.name;
}

struct EventPlayerReady : SignalEvent {};
struct EventPlayerDisconncted : SignalEvent {};

// Register new Events here
typedef Events<EventPlayerConnected, EventPlayerReady, EventPlayerDisconncted>
    Event;
