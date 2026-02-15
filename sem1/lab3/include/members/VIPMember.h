#pragma once
#include "Member.h"

class VIPMember : public Member {
public:
    VIPMember(const std::string& name, int memberId);
    void accessPremiumContent();
    void requestPriorityLoan();

private:
    int priorityLevel;
};