#pragma once
#include <string>
#include <iostream>

class Ticket
{
private:
    std::string ticketStatus;
    int ticketNumber;

public:
    Ticket(int number, std::string status);
    std::string getTicketStatus();
    void setTicketStatus(std::string status);
    int getTicketNumber();
};