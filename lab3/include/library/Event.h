#pragma once
#include <string>

class Event {
public:
    Event(const std::string& name, const std::string& date);
    void changeDate(const std::string& newDate);
    std::string getEventDate() const;

private:
    std::string eventName;
    std::string eventDate;
};