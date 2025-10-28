#pragma once
#include <string>
#include <vector>

class Client;
class Passenger;
class PaymentMethod;
class Driver;
class Vehicle;
enum class OrderStatus
{
    Pending,
    InProgress,
    Completed
};

class IOrder
{
public:
    virtual std::string getOrderId() = 0;
    virtual std::vector<Passenger> getPassengers() = 0;
    virtual PaymentMethod *getPaymentType() = 0;
    virtual double getCargoWeight() = 0;
    virtual Vehicle *getVehicle() = 0;
    virtual OrderStatus getStatus() = 0;
    virtual void setStatus(OrderStatus status) = 0;
    virtual double calculateCost() = 0;
    virtual double getTotalCost() = 0;
    virtual void createOrder(std::string orderId, std::vector<Passenger> passengersList,
                             PaymentMethod *paymentType, double weightOfOrder, Vehicle *vehicle) = 0;
    virtual Client *getCustomer() const = 0;
    virtual void assignVehicleAndEmployee(Vehicle *vehicle, Driver *driver) = 0;
    virtual ~IOrder() = default;
};