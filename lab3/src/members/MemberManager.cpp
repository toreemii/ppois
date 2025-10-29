#include "MemberManager.h"
#include "LibraryExceptions.h"

void MemberManager::addMemberToRecords(Member& memberToAdd) {
    managedMembers.push_back(memberToAdd);
}

void MemberManager::removeMemberFromRecords(int memberIdToRemove) {
    for (size_t index = 0; index < managedMembers.size(); ++index) {
        if (managedMembers[index].getMemberShipId() == memberIdToRemove) {
            managedMembers.erase(managedMembers.begin() + index);
            return;
        }
    }
}

Member MemberManager::findMemberById(int memberIdToFind) {
    for (size_t index = 0; index < managedMembers.size(); ++index) {
        if (managedMembers[index].getMemberShipId() == memberIdToFind) {
            return managedMembers[index];
        }
    }
    LibraryExceptions::throwMemberNotFound("Участник не найден");
    return Member("", 0);
}