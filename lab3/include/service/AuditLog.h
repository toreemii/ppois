#pragma once
#include <vector>
#include <string>

class AuditLog {
public:
    void logAction(const std::string& action);
    void clearLog();

private:
    std::vector<std::string> logEntries;
};