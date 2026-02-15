#include "EventRoom.h"
#include <iostream>

EventRoom::EventRoom() : Room("Мероприятия"), currentEventName("") {}

void EventRoom::scheduleEvent(const std::string& eventName) {
    if (!eventName.empty()) {
        currentEventName = eventName;
        std::cout << "Мероприятие запланировано: " << eventName << std::endl;
    }
}

void EventRoom::cancelEvent() {
    if (!currentEventName.empty()) {
        currentEventName = "";
        std::cout << "Мероприятие отменено" << std::endl;
    }
}