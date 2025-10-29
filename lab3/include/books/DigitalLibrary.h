#pragma once
#include "EBook.h"
#include <vector>

class DigitalLibrary {
public:
    void uploadEBook(EBook& ebookToUpload);
    void removeEBook(const std::string& title);
    EBook getEBook(const std::string& title) const;

private:
    std::vector<EBook> digitalCollection;
};