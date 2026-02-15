#pragma once
#include <string>
#include <vector>
#include "Order.h"

class IOrder;

class IClient
{
public:
    virtual std::string getClientId() const = 0;
    virtual std::string getName() const = 0;
    virtual std::string getAddress() const = 0;
    virtual std::string getPhoneNumber() const = 0;
    virtual std::string getEmail() const = 0;
    virtual void setEmail(std::string email) = 0;
    virtual void setPhoneNumber(std::string phoneNumber) = 0;
    virtual void updateContactInfo(std::string newPhone, std::string newEmail) = 0;
    virtual std::vector<Order> getOrders() const = 0;
    virtual void placeOrder(Order *order) = 0;
    virtual double getDiscountRate() const = 0;
    virtual void setDiscountRate(double rate) = 0;
    virtual int getLoyaltyPoints() const = 0;
    virtual std::tm getLastOrderDate() const = 0;
};