#pragma once
#include <vector>
#include "Branch.h"

class Library {
public:
    Library(const std::string& libraryName);
    void addBranchToLibrary(Branch& branchToAdd);
    void checkCapacity();

private:
    std::string mainLibraryName;
    std::vector<Branch> libraryBranches;
    int maxBranchesAllowed;
};