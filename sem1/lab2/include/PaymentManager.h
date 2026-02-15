#pragma once
#include "PaymentMethod.h"
#include "Client.h"
#include "Order.h"
#include "Vehicle.h"
#include "Passenger.h"
#include "Exceptions.h"

class Client;

class PaymentManager {
public:
    void makePayment(int choice);
    void makeOrderPayment(Client* client, std::string orderId, std::vector<Passenger> passengersList, 
                          PaymentMethod* paymentType, double weightOfOrder, Vehicle* vehicle);
};