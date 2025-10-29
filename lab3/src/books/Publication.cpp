#include "Publication.h"

Publication::Publication(const std::string& title, const std::string& authorName)
    : publicationTitle(title), publicationAuthor(authorName) {}

std::string Publication::getPublicationTitle() const {
    return publicationTitle;
}

std::string Publication::getAuthorName() const {
    return publicationAuthor;
}