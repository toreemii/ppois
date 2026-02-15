#pragma once
#include <string>

class Employee
{
protected:
    std::string employeeId;
    std::string firstName;
    std::string lastName;

public:
    Employee(std::string employeeId, std::string firstName, std::string lastName);
    Employee() {}
    std::string getEmployeeId();
};