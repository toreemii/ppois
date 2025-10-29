#pragma once
#include <string>
#include <vector>
#include "Shelf.h"

class Branch {
public:
    Branch(const std::string& locationName);
    void addShelfToBranch(Shelf& shelfToAdd);
    void organizeShelves();

private:
    std::string branchLocationName;
    std::vector<Shelf> shelvesInBranch;
};