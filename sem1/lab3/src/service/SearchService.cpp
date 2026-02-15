#include "SearchService.h"
#include "LibraryExceptions.h"

void SearchService::indexBook(Book& bookToIndex) {
    indexedBooks.push_back(bookToIndex);
}

std::vector<Book> SearchService::searchByTitle(const std::string& titleQuery) const {
    std::vector<Book> results;
    for (size_t index = 0; index < indexedBooks.size(); ++index) {
        if (indexedBooks[index].getPublicationTitle().find(titleQuery) != std::string::npos) {
            results.push_back(indexedBooks[index]);
        }
    }
    if (results.empty()) {
        LibraryExceptions::throwBookNotFound("Книги не найдены");
    }
    return results;
}

std::vector<Book> SearchService::searchByAuthor(const std::string& authorQuery) const {
    std::vector<Book> results;
    for (size_t index = 0; index < indexedBooks.size(); ++index) {
        if (indexedBooks[index].getAuthorName().find(authorQuery) != std::string::npos) {
            results.push_back(indexedBooks[index]);
        }
    }
    if (results.empty()) {
        LibraryExceptions::throwBookNotFound("Книги не найдены");
    }
    return results;
}