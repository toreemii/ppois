#pragma once
#include <vector>
#include "Member.h"

class MemberManager {
public:
    void addMemberToRecords(Member& memberToAdd);
    void removeMemberFromRecords(int memberIdToRemove);
    Member findMemberById(int memberIdToFind);

private:
    std::vector<Member> managedMembers;
};