#pragma once
#include <string>
#include "Client.h"
#include "Order.h"
#include "Manager.h"

class Feedback
{
private:
    int rating;
    std::string comment;
    Client *client;
    Order *feedbackOrder;

public:
    Feedback(int rating, std::string comment, Client *client, Order *order);
    void submitFeedback(Order *order, int rate, std::string comment);
    void escalateToManager(Manager *manager);
    int getRating();
};