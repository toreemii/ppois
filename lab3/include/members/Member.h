#pragma once
#include <string>

class Member {
public:
    Member(const std::string& name, int memberId);
    void renewMembership();
    void updateMembershipStatus();
    int getMemberShipId();
    std::string getMemberFullName();

protected:
    std::string memberFullName;
    int membershipId;
    bool isActiveMember;
};