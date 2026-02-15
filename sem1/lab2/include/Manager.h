#pragma once
#include "Employee.h"
#include <vector>
#include "Order.h"
#include "License.h"
#include <iostream>
class Manager : public Employee
{
private:
    std::vector<Employee> subordinates;
    std::vector<Order> managedOrders;
    std::string managerId;

public:
    Manager(std::string employeeId, std::string firstName, std::string lastName);
    void approveOrder(Order order);
    std::string getManagerId();
};