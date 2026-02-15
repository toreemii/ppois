#include "Shelf.h"
#include "LibraryExceptions.h"

Shelf::Shelf(int capacity) : shelfCapacity(capacity) {}

void Shelf::addBookToShelf(Book& bookToAdd) {
    if (static_cast<int>(booksOnShelf.size()) >= shelfCapacity) {
        LibraryExceptions::throwLibraryFull("Полка переполнена");
    }
    booksOnShelf.push_back(bookToAdd);
}

void Shelf::removeBookFromShelf(const std::string& titleToRemove) {
    for (size_t index = 0; index < booksOnShelf.size(); ++index) {
        if (booksOnShelf[index].getPublicationTitle() == titleToRemove) {
            booksOnShelf.erase(booksOnShelf.begin() + index);
            return;
        }
    }
}

int Shelf::getShelfCapacity() const {
    return shelfCapacity;
}