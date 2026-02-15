#pragma once
#include <string>

class Staff {
public:
    Staff(const std::string& name, int employeeId);
    void clockIn();
    void clockOut();

protected:
    std::string staffFullName;
    int employeeIdentification;
    bool isOnDuty;
};