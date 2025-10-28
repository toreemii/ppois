#include "../include/Manager.h"

Manager::Manager(std::string employeeId, std::string firstName, std::string lastName)
    : Employee(employeeId, firstName, lastName) {}

void Manager::approveOrder(Order order)
{
    std::cout << "Заказ одобрен менеджером\n";
}

std::string Manager::getManagerId()
{
    return managerId;
}
