#include "../include/PaymentProcessor.h"

PaymentProcessor::PaymentProcessor(std::string processorId) : processorId(processorId) {}

std::string PaymentProcessor::getProcessorId()
{
    return processorId;
}
bool PaymentProcessor::processPayment(Client *client, PaymentMethod *payment, double amount)
{
    client->makePayment(1);
    std::cout << "Платёж на сумму " << amount << " обработан для клиента " << client->getClientId() << ": " << processorId << std::endl;
    return true;
}