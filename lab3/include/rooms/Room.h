#pragma once
#include <string>
#include <vector>
#include "Shelf.h"

class Room {
public:
    Room(const std::string& roomType);
    void addShelfToRoom(Shelf& shelfToAdd);
    void cleanRoom();

private:
    std::string roomDescription;
    std::vector<Shelf> shelvesInRoom;
};