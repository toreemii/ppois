#pragma once
#include "Room.h"

class EventRoom : public Room {
public:
    EventRoom();
    void scheduleEvent(const std::string& eventName);
    void cancelEvent();

private:
    std::string currentEventName;
};