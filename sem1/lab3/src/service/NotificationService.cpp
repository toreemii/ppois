#include "NotificationService.h"
#include <iostream>

void NotificationService::sendOverdueNotification(Member& memberToNotify, const std::string& message) {
    if (!message.empty()) {
        notificationLog += message;
        std::cout << "Отправлено " << memberToNotify.getMemberFullName() << std::endl;
    }
}

void NotificationService::sendReservationConfirmation(Member& memberToConfirm, const std::string& details) {
    if (!details.empty()) {
        notificationLog += details;
        std::cout << "Подтверждено для " << memberToConfirm.getMemberFullName() << std::endl;
    }
}