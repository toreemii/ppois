#pragma once
#include <vector>
#include "Reservation.h"

class ReservationManager {
public:
    void addReservationToRecords(Reservation& reservationToAdd);
    void removeReservationForBook(const std::string& bookTitle);
    Reservation findReservationByBook(const std::string& bookTitle) const;

private:
    std::vector<Reservation> managedReservations;
};