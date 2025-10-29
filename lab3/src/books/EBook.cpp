#include "EBook.h"
#include <iostream>

EBook::EBook(const std::string& title, const std::string& authorName, const std::string& formatType)
    : Publication(title, authorName), fileFormatType(formatType) {}

void EBook::openToPage(int pageNumber) {
    std::cout << "Открыто в электронном виде на странице " << pageNumber << std::endl;
}

void EBook::download() {
    if (!fileFormatType.empty()) {
        std::cout << "Скачивание " << publicationTitle << std::endl;
    }
}

void EBook::zoomIn() {
    std::cout << "Увеличение масштаба " << publicationTitle << std::endl;
}