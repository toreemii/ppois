#pragma once
#include "Publication.h"
#include <string>

class Magazine : public Publication {
public:
    Magazine(const std::string& title, const std::string& authorName, int issueMonth);
    void openToPage(int pageNumber) override;
    void flipToPage(int page);
    void subscribe();

private:
    int magazineIssueMonth;
};