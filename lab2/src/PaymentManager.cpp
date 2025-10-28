#include "../include/PaymentManager.h"
#include "../include/Exceptions.h"
#include "../include/Order.h"

void PaymentManager::makePayment(int choice)
{
    PaymentMethod *payment;
    switch (choice)
    {
    case 1:
        payment = new CardPayment();
        break;
    case 2:
        payment = new CashPayment();
        break;
    case 3:
        payment = new CheckPayment();
        break;
    default:
        throw InvalidPaymentException();
    }
    payment->processPayment();
    delete payment;
}

void PaymentManager::makeOrderPayment(Client *client, std::string orderId, std::vector<Passenger> passengersList,
                                      PaymentMethod *paymentType, double weightOfOrder, Vehicle *vehicle)
{
    Order order(orderId, passengersList, paymentType, weightOfOrder, vehicle, client);
    client->placeOrder(&order);
}