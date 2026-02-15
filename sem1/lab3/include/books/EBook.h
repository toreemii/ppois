#pragma once
#include "Publication.h"
#include <string>

class EBook : public Publication {
public:
    EBook(const std::string& title, const std::string& authorName, const std::string& formatType);
    void openToPage(int pageNumber) override;
    void download();
    void zoomIn();

private:
    std::string fileFormatType;
};