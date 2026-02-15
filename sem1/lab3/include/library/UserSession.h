#pragma once
#include <string>

class UserSession {
public:
    UserSession(int sessionId);
    void start();
    void end();

private:
    int sessionIdentification;
    std::string startTime;
    bool isActive;
};