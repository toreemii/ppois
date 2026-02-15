#include "Magazine.h"
#include <iostream>

Magazine::Magazine(const std::string& title, const std::string& authorName, int issueMonth)
    : Publication(title, authorName), magazineIssueMonth(issueMonth) {}

void Magazine::openToPage(int pageNumber) {
    std::cout << "Открыт журнал на странице " << pageNumber << std::endl;
}

void Magazine::flipToPage(int page) {
    if (page > 0) {
        std::cout << "Перелистнуто на страницу " << page << std::endl;
    }
}

void Magazine::subscribe() {
    std::cout << "Подписка на " << publicationTitle << std::endl;
}