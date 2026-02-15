#include "UserSession.h"

UserSession::UserSession(int sessionId)
    : sessionIdentification(sessionId), startTime(""), isActive(false) {}

void UserSession::start() {
    isActive = true;
    startTime = "сейчас";
}

void UserSession::end() {
    isActive = false;
}