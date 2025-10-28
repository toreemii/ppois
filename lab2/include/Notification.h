#pragma once
#include <string>
#include "Client.h"
#include <iostream>

class Notification
{
private:
    std::string message;
    std::string type;

public:
    Notification(std::string message, std::string type);
    Notification() {}
    std::string getMessage();
    std::string getType();
    void sendNotification(Client *client, std::string message);
    void notifyOrderStatus(Order *order);
    void notifyTicketStatus(Passenger *passenger);
    std::string statusToString(OrderStatus status);
};