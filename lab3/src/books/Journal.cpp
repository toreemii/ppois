#include "Journal.h"
#include <iostream>

Journal::Journal(const std::string& title, const std::string& authorName, int issueNumber)
    : Publication(title, authorName), journalIssueNumber(issueNumber) {}

void Journal::openToPage(int pageNumber) {
    std::cout << "Открыт журнал на странице " << pageNumber << std::endl;
}

void Journal::citeArticle() {
    std::cout << "Цитирование статьи из выпуска " << journalIssueNumber << std::endl;
}

void Journal::archiveIssue() {
    if (journalIssueNumber > 0) {
        std::cout << "Архивирован выпуск " << journalIssueNumber << std::endl;
    }
}