#include "BookCopy.h"

BookCopy::BookCopy(const Book& originalBook, int copyId)
    : originalBookReference(originalBook), copyIdentification(copyId), isAvailable(true) {}

void BookCopy::markAsAvailable() {
    isAvailable = true;
}

void BookCopy::markAsBorrowed() {
    if (isAvailable) {
        isAvailable = false;
    }
}