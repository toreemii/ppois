#pragma once
#include <string>

class Publication {
public:
    Publication(const std::string& title, const std::string& authorName);
    virtual void openToPage(int pageNumber) = 0;
    virtual ~Publication() = default;

    std::string getPublicationTitle() const;
    std::string getAuthorName() const;

protected:
    std::string publicationTitle;
    std::string publicationAuthor;
};