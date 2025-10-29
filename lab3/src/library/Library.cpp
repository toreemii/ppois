#include "Library.h"
#include "LibraryExceptions.h"

Library::Library(const std::string& libraryName) : mainLibraryName(libraryName), maxBranchesAllowed(5) {}

void Library::addBranchToLibrary(Branch& branchToAdd) {
    if (libraryBranches.size() >= static_cast<size_t>(maxBranchesAllowed)) {
        LibraryExceptions::throwLibraryFull("Нет места для нового филиала");
    }
    libraryBranches.push_back(branchToAdd);
}

void Library::checkCapacity() {
    if (libraryBranches.size() < static_cast<size_t>(maxBranchesAllowed)) {
    }
}