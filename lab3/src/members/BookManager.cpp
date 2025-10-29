#include "BookManager.h"
#include "LibraryExceptions.h"

void BookManager::addBookToCollection(Book& bookToAdd) {
    for (size_t index = 0; index < managedBooksCollection.size(); ++index) {
        if (managedBooksCollection[index].getPublicationTitle() == bookToAdd.getPublicationTitle()) {
            LibraryExceptions::throwDuplicateBook("Книга уже существует");
        }
    }
    managedBooksCollection.push_back(bookToAdd);
}

void BookManager::removeBookFromCollection(const std::string& titleToRemove) {
    for (size_t index = 0; index < managedBooksCollection.size(); ++index) {
        if (managedBooksCollection[index].getPublicationTitle() == titleToRemove) {
            managedBooksCollection.erase(managedBooksCollection.begin() + index);
            return;
        }
    }
}

Book BookManager::findBookByTitle(const std::string& titleToFind) const {
    for (size_t index = 0; index < managedBooksCollection.size(); ++index) {
        if (managedBooksCollection[index].getPublicationTitle() == titleToFind) {
            return managedBooksCollection[index];
        }
    }
    LibraryExceptions::throwBookNotFound("Книга не найдена");
    return Book("", "", 0);
}