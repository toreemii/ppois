#include "../include/Employee.h"

Employee::Employee(std::string employeeId, std::string firstName, std::string lastName)
    : employeeId(employeeId), firstName(firstName), lastName(lastName) {}

std::string Employee::getEmployeeId()
{
    return employeeId;
}