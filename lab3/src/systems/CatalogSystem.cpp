#include "CatalogSystem.h"

void CatalogSystem::registerBook(Book& bookToRegister) {
    catalogedBooks.push_back(bookToRegister);
}

void CatalogSystem::updateBookStatus(const std::string& title, bool isAvailable) {
    for (size_t index = 0; index < catalogedBooks.size(); ++index) {
        if (catalogedBooks[index].getPublicationTitle() == title) {
            break;
        }
    }
}

std::vector<Book> CatalogSystem::getAllBooks() const {
    return catalogedBooks;
}