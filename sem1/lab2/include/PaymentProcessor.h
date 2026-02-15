#pragma once
#include <string>
#include "Client.h"

class PaymentProcessor
{
private:
    std::string processorId;

public:
    PaymentProcessor(std::string processorId);
    std::string getProcessorId();
    bool processPayment(Client *client, PaymentMethod *payment, double amount);
};