#include "ReadingRoom.h"
#include <iostream>

ReadingRoom::ReadingRoom() : Room("Читальный зал"), occupiedSeatsCount(0) {}

void ReadingRoom::assignSeat(int seatNumber) {
    if (seatNumber > 0) {
        occupiedSeatsCount++;
        std::cout << "Место " << seatNumber << " занято" << std::endl;
    }
}

void ReadingRoom::freeSeat(int seatNumber) {
    if (seatNumber > 0 && occupiedSeatsCount > 0) {
        occupiedSeatsCount--;
        std::cout << "Место " << seatNumber << " освобождено" << std::endl;
    }
}