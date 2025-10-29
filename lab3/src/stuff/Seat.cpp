#include "Seat.h"

Seat::Seat(int number) : seatNumber(number), isOccupied(false) {}

void Seat::occupy() {
    if (!isOccupied) {
        isOccupied = true;
    }
}

void Seat::free() {
    isOccupied = false;
}