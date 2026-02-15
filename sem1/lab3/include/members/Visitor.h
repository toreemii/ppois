#pragma once
#include <string>

class Visitor {
public:
    Visitor(const std::string& name, const std::string& purpose);
    void recordEntry();
    void recordExit();

private:
    std::string visitorName;
    std::string visitPurpose;
    std::string entryTime;
};