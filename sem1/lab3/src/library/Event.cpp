#include "Event.h"

Event::Event(const std::string& name, const std::string& date)
    : eventName(name), eventDate(date) {}

void Event::changeDate(const std::string& newDate) {
    if (!newDate.empty()) {
        eventDate = newDate;
    }
}

std::string Event::getEventDate() const {
    return eventDate;
}