#pragma once
#include "Room.h"

class ArchiveRoom : public Room {
public:
    ArchiveRoom();
    void secureDocuments();
    void logAccess();

private:
    bool isSecured;
};