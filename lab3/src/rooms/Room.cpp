#include "Room.h"

Room::Room(const std::string& roomType) : roomDescription(roomType) {}

void Room::addShelfToRoom(Shelf& shelfToAdd) {
    shelvesInRoom.push_back(shelfToAdd);
}

void Room::cleanRoom() {
    if (!shelvesInRoom.empty()) {
        // Уборка
    }
}