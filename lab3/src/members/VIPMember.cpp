#include "VIPMember.h"
#include <iostream>

VIPMember::VIPMember(const std::string& name, int memberId) : Member(name, memberId), priorityLevel(1) {}

void VIPMember::accessPremiumContent() {
    if (priorityLevel > 0) {
        std::cout << "Доступ к премиум для " << memberFullName << std::endl;
    }
}

void VIPMember::requestPriorityLoan() {
    priorityLevel++;
}