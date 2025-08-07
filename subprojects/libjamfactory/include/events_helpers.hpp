#pragma once

#include "type_name/type_name.hpp"
#include <SFML/Network/Packet.hpp>
#include <concepts>
#include <string>
#include <variant>

template <typename T>
concept Sendable = requires(sf::Packet &packet, T &ev) {
    { packet << ev } -> std::same_as<sf::Packet &>;
    { packet >> ev } -> std::same_as<sf::Packet &>;
};

// Events that don't transfere data
struct SignalEvent {
    friend sf::Packet &operator<<(sf::Packet &packet, const SignalEvent &) {
        return packet;
    }
    friend sf::Packet &operator>>(sf::Packet &packet, const SignalEvent &) {
        return packet;
    }
};

// TODO: writte a smarter helper explicitly for Events since existing types are
// known at compile time
// helper type for the visitor (std::variant::visit)
template <typename... Ts> struct overloaded : Ts... {
    using Ts::operator()...;
};

// helper for Event
template <Sendable... Ts> struct Events : std::variant<Ts...> {
    using std::variant<Ts...>::operator=;

    [[nodiscard]] std::string getTypeName() const {
        return std::visit(
            overloaded{[](Ts) { return std::string(type_name_v<Ts>); }...},
            *this);
    }
};

template <Sendable... Ts>
inline sf::Packet &operator<<(sf::Packet &packet, const Events<Ts...> &m) {
    std::visit(overloaded{[&packet](Ts ev) {
                   packet << std::string(type_name_v<Ts>) << ev;
               }...},
               m);

    return packet;
}

template <Sendable T, Sendable... Ts>
void check_event_package_type(sf::Packet &packet, Events<Ts...> &m,
                              const std::string &type) {
    if (type == type_name_v<T>) {
        T ev;
        packet >> ev;
        m = ev;
    }
}

template <Sendable... Ts>
inline sf::Packet &operator>>(sf::Packet &packet, Events<Ts...> &m) {
    std::string type;
    packet >> type;

    (check_event_package_type<Ts>(packet, m, type), ...);

    return packet;
}
