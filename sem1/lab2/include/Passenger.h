#pragma once
#include "Order.h"
#include <vector>
#include <iostream>
#include <string>
#include "Ticket.h"

class Order;

class Passenger
{
private:
    std::string passengerId;
    std::string firstName;
    std::string lastName;
    Ticket *ticket;
    Order *order;
    std::string contactNumber;
    std::string travelPreferences;
    std::string emergencyContact;

public:
    Passenger(std::string passengerId, std::string firstName, std::string lastName);
    void checkIn(std::string status);
    bool hasValidTicket();
    void setTicket(Ticket *t);
    void setOrder(Order *o);
    std::string getPassengerId();
    Ticket *getTicket();
    Order *getOrder();
    void setContactNumber(std::string contactNumber);
    std::string getContactNumber();
};