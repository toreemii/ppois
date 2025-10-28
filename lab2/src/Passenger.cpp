#include "../include/Passenger.h"

Passenger::Passenger(std::string passengerId, std::string firstName, std::string lastName)
    : passengerId(passengerId), firstName(firstName), lastName(lastName), ticket(nullptr), order(nullptr) {}

void Passenger::checkIn(std::string status)
{
    if (hasValidTicket())
    {
        ticket->setTicketStatus(status);
        std::cout << "Пассажир " << passengerId << "зарегистрировался" << std::endl;
    }
    else
    {
        throw std::runtime_error("Неверный билет");
    }
}

void Passenger::setContactNumber(std::string contactNumber)
{
    this->contactNumber = contactNumber;
}

std::string Passenger::getContactNumber()
{
    return contactNumber;
}

bool Passenger::hasValidTicket()
{
    return ticket != nullptr && ticket->getTicketStatus() != "Отменен";
}

void Passenger::setTicket(Ticket *t)
{
    ticket = t;
}
void Passenger::setOrder(Order *o)
{
    order = o;
}
std::string Passenger::getPassengerId()
{
    return passengerId;
}
Ticket *Passenger::getTicket()
{
    return ticket;
}
Order *Passenger::getOrder()
{
    return order;
}
