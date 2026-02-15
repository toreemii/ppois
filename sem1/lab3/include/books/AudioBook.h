#pragma once
#include "Publication.h"
#include <string>

class AudioBook : public Publication {
public:
    AudioBook(const std::string& title, const std::string& authorName, int durationInMinutes);
    void openToPage(int pageNumber) override;
    void playSample();
    void adjustVolume(int level);

private:
    int audioDurationInMinutes;
};