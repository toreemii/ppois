#include "Author.h"
#include "LibraryExceptions.h"

Author::Author(const std::string& fullName) : authorFullName(fullName) {}

void Author::addWrittenBook(Book& bookToAdd) {
    if (bookToAdd.getPublicationTitle().empty()) {
        LibraryExceptions::throwInvalidAuthor("Пустое название книги");
    }
    writtenBooksList.push_back(bookToAdd);
}

std::vector<Book> Author::getWrittenBooks() const {
    return writtenBooksList;
}