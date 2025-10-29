#include "Category.h"
#include "LibraryExceptions.h"

Category::Category(const std::string& categoryName) : categoryDescription(categoryName) {}

void Category::assignBookToCategory(Book& bookToAssign) {
    booksInCategory.push_back(bookToAssign);
}

void Category::validateCategory() {
    if (categoryDescription.empty()) {
        LibraryExceptions::throwInvalidCategory("Пустое описание категории");
    }
}