#pragma once

struct EventPlayerConnected {
    std::string name;
};

enum EventType { PlayerConnected };

class Event {
  public:
    EventType type;

    union {
        EventPlayerConnected playerConnected;
    };
};
