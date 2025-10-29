#pragma once
#include "Publication.h"
#include <string>

class Journal : public Publication {
public:
    Journal(const std::string& title, const std::string& authorName, int issueNumber);
    void openToPage(int pageNumber) override;
    void citeArticle();
    void archiveIssue();

private:
    int journalIssueNumber;
};