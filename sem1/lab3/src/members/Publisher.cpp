#include "Publisher.h"
#include "LibraryExceptions.h"

Publisher::Publisher(const std::string& companyName) : publisherCompanyName(companyName) {}

void Publisher::publishBook(Book& bookToPublish) {
    publishedBooksList.push_back(bookToPublish);
}

void Publisher::validatePublisher() {
    if (publisherCompanyName.empty()) {
        LibraryExceptions::throwInvalidPublisher("Пустое название издателя");
    }
}