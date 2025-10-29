#pragma once
#include "Room.h"

class ReadingRoom : public Room {
public:
    ReadingRoom();
    void assignSeat(int seatNumber);
    void freeSeat(int seatNumber);

private:
    int occupiedSeatsCount;
};