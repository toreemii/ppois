#pragma once
class Seat {
public:
    Seat(int number);
    void occupy();
    void free();

private:
    int seatNumber;
    bool isOccupied;
};