#include "../include/Order.h"
#include "../include/Exceptions.h"
#include <iostream>

Order::Order(std::string orderId, std::vector<Passenger> passengers, PaymentMethod *paymentType,
             double cargoWeight, Vehicle *vehicle, Client *customer, Driver *driver)
    : orderId(orderId), passengers(passengers), paymentType(paymentType), cargoWeight(cargoWeight),
      vehicle(vehicle), customer(customer), driver(driver), status(OrderStatus::Pending)
{
    if (paymentType == nullptr || vehicle == nullptr || customer == nullptr)
    {
        throw InvalidArgumentException();
    }
    totalCost = calculateCost();
}

void Order::createOrder(std::string orderId, std::vector<Passenger> passengersList, PaymentMethod *paymentType,
                        double weightOfOrder, Vehicle *vehicle)
{
    if (paymentType == nullptr || vehicle == nullptr)
    {
        throw InvalidArgumentException();
    }
    this->orderId = orderId;
    this->passengers = passengersList;
    this->paymentType = paymentType;
    this->cargoWeight = weightOfOrder;
    this->vehicle = vehicle;
    this->totalCost = calculateCost();
}

std::string Order::getOrderId()
{
    return orderId;
}
std::vector<Passenger> Order::getPassengers()
{
    return passengers;
}
PaymentMethod *Order::getPaymentType()
{
    return paymentType;
}
double Order::getCargoWeight()
{
    return cargoWeight;
}
Vehicle *Order::getVehicle()
{
    return vehicle;
}
OrderStatus Order::getStatus()
{
    return status;
}
void Order::setStatus(OrderStatus status)
{
    this->status = status;
}
double Order::calculateCost()
{
    return cargoWeight * 10.0;
}
double Order::getTotalCost() { return totalCost; }

Client *Order::getCustomer() const
{
    return customer;
}

void Order::assignVehicleAndEmployee(Vehicle *vehicle, Driver *driver)
{
    if (vehicle == nullptr || driver == nullptr)
    {
        throw InvalidArgumentException();
    }
    this->vehicle = vehicle;
    this->driver = driver;
    vehicle->assignDriver(*driver);
    std::cout << "Транспорт " << vehicle->getVehicleId() << " и водитель " << driver->getLicenseType()
              << " назначены на заказ " << orderId << std::endl;
}