#include "DigitalLibrary.h"
#include "LibraryExceptions.h"

void DigitalLibrary::uploadEBook(EBook& ebookToUpload) {
    digitalCollection.push_back(ebookToUpload);
}

void DigitalLibrary::removeEBook(const std::string& title) {
    for (size_t index = 0; index < digitalCollection.size(); ++index) {
        if (digitalCollection[index].getPublicationTitle() == title) {
            digitalCollection.erase(digitalCollection.begin() + index);
            return;
        }
    }
}

EBook DigitalLibrary::getEBook(const std::string& title) const {
    for (size_t index = 0; index < digitalCollection.size(); ++index) {
        if (digitalCollection[index].getPublicationTitle() == title) {
            return digitalCollection[index];
        }
    }
    LibraryExceptions::throwBookNotFound("Электронная книга не найдена");
    return EBook("", "", "");
}