#include "../include/Ticket.h"

Ticket::Ticket(int number, std::string status) : ticketNumber(number), ticketStatus(status) {}

std::string Ticket::getTicketStatus()
{
    return ticketStatus;
}
void Ticket::setTicketStatus(std::string status)
{
    this->ticketStatus = status;
    std::cout << "Билет " << ticketNumber << " статус изменён на " << status << std::endl;
}

int Ticket::getTicketNumber()
{
    return ticketNumber;
}
