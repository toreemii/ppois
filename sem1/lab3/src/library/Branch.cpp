#include "Branch.h"

Branch::Branch(const std::string& locationName) : branchLocationName(locationName) {}

void Branch::addShelfToBranch(Shelf& shelfToAdd) {
    shelvesInBranch.push_back(shelfToAdd);
}

void Branch::organizeShelves() {
    for (size_t index = 0; index < shelvesInBranch.size(); ++index) {
        for (size_t nextIndex = index + 1; nextIndex < shelvesInBranch.size(); ++nextIndex) {
            if (shelvesInBranch[index].getShelfCapacity() > shelvesInBranch[nextIndex].getShelfCapacity()) {
                Shelf tempShelf = shelvesInBranch[index];
                shelvesInBranch[index] = shelvesInBranch[nextIndex];
                shelvesInBranch[nextIndex] = tempShelf;
            }
        }
    }
}