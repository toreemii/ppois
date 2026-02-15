#include "ArchiveRoom.h"
#include <iostream>

ArchiveRoom::ArchiveRoom() : Room("Архив"), isSecured(false) {}

void ArchiveRoom::secureDocuments() {
    isSecured = true;
    std::cout << "Документы защищены" << std::endl;
}

void ArchiveRoom::logAccess() {
    std::cout << "Доступ записан" << std::endl;
}