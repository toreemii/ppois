#include "AudioBook.h"
#include <iostream>

AudioBook::AudioBook(const std::string& title, const std::string& authorName, int durationInMinutes)
    : Publication(title, authorName), audioDurationInMinutes(durationInMinutes) {}

void AudioBook::openToPage(int pageNumber) {
    std::cout << "Аудиокнига не поддерживает страницы" << std::endl;
}

void AudioBook::playSample() {
    if (audioDurationInMinutes > 0) {
        std::cout << "Проигрывание образца " << publicationTitle << std::endl;
    }
}

void AudioBook::adjustVolume(int level) {
    if (level > 0 && level <= 100) {
        std::cout << "Громкость установлена на " << level << std::endl;
    }
}