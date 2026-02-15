#pragma once
#include "Member.h"
#include <string>

class NotificationService {
public:
    void sendOverdueNotification(Member& memberToNotify, const std::string& message);
    void sendReservationConfirmation(Member& memberToConfirm, const std::string& details);

private:
    std::string notificationLog;
};