#include "Staff.h"

Staff::Staff(const std::string& name, int employeeId) : staffFullName(name), employeeIdentification(employeeId), isOnDuty(false) {}

void Staff::clockIn() {
    isOnDuty = true;
}

void Staff::clockOut() {
    isOnDuty = false;
}