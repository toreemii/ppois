#include "Visitor.h"

Visitor::Visitor(const std::string& name, const std::string& purpose)
    : visitorName(name), visitPurpose(purpose), entryTime("") {}

void Visitor::recordEntry() {
    entryTime = "сейчас";
}

void Visitor::recordExit() {
    entryTime = "";
}