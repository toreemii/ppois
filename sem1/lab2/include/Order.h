#pragma once
#include <string>
#include <vector>
#include "Passenger.h"
#include "Vehicle.h"
#include "PaymentMethod.h"
#include "IOrder.h"

class Client;
class Passenger;
class Driver;

class Order : public IOrder {
private:
    std::string orderId;
    std::vector<Passenger> passengers;
    PaymentMethod* paymentType;
    double cargoWeight;
    Vehicle* vehicle;
    Driver* driver; 
    Client* customer; 
    OrderStatus status;
    double totalCost;

public:
    Order(std::string orderId, std::vector<Passenger> passengers, PaymentMethod* paymentType, double cargoWeight, 
          Vehicle* vehicle, Client* customer, Driver* driver = nullptr);
    std::string getOrderId() override;
    std::vector<Passenger> getPassengers() override;
    PaymentMethod* getPaymentType() override;
    double getCargoWeight() override;
    Vehicle* getVehicle() override;
    OrderStatus getStatus() override;
    void setStatus(OrderStatus status) override;
    double calculateCost() override;
    double getTotalCost() override;
    void createOrder(std::string orderId, std::vector<Passenger> passengersList, PaymentMethod* paymentType,
                     double weightOfOrder, Vehicle* vehicle) override;
    Client* getCustomer() const;
    void assignVehicleAndEmployee(Vehicle* vehicle, Driver* driver); 
};