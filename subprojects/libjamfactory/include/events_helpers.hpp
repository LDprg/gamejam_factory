#pragma once

#include <SFML/Network/Packet.hpp>
#include <string>
#include <variant>

#include "type_name/type_name.hpp"

// Events that don't transfere data
struct SignalEvent {
    friend sf::Packet &operator<<(sf::Packet &packet, const SignalEvent &) {
        return packet;
    }
    friend sf::Packet &operator>>(sf::Packet &packet, SignalEvent &) {
        return packet;
    }
};

// helper for Event
template <typename... Ts> struct Events : std::variant<Ts...> {
    using std::variant<Ts...>::operator=;
};

// TODO: writte a smarter helper explicitly for Events since existing types are
// known at compile time
// helper type for the visitor (std::variant::visit)
template <class... Ts> struct overloaded : Ts... {
    using Ts::operator()...;
};

template <typename... Ts>
inline sf::Packet &operator<<(sf::Packet &packet, const Events<Ts...> &m) {
    std::visit(overloaded{[&packet](Ts ev) {
                   packet << std::string(type_name_v<Ts>) << ev;
               }...},
               m);

    return packet;
}

template <typename T, typename... Ts>
void check_event_package_type(sf::Packet &packet, Events<Ts...> &m,
                              const std::string &type) {
    if (type == type_name_v<T>) {
        T ev;
        packet >> ev;
        m = ev;
    }
}

template <typename... Ts>
inline sf::Packet &operator>>(sf::Packet &packet, Events<Ts...> &m) {
    std::string type;
    packet >> type;

    (check_event_package_type<Ts>(packet, m, type), ...);

    return packet;
}
