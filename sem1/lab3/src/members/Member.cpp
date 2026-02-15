#include "Member.h"
#include "LibraryExceptions.h"

Member::Member(const std::string& name, int memberId) : memberFullName(name), membershipId(memberId), isActiveMember(true) {}

void Member::renewMembership() {
    isActiveMember = true;
}

void Member::updateMembershipStatus() {
    if (membershipId <= 0) {
        LibraryExceptions::throwInvalidMember("Некорректный ID участника");
    }
}

int Member::getMemberShipId() {
    return membershipId;
}

std::string Member::getMemberFullName() {
    return memberFullName;
}