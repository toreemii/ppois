#pragma once
#include <string>
#include <vector>
#include "Book.h"

class Publisher {
public:
    Publisher(const std::string& companyName);
    void publishBook(Book& bookToPublish);
    void validatePublisher();

private:
    std::string publisherCompanyName;
    std::vector<Book> publishedBooksList;
};