#include "ReservationManager.h"
#include "LibraryExceptions.h"

void ReservationManager::addReservationToRecords(Reservation& reservationToAdd) {
    managedReservations.push_back(reservationToAdd);
}

void ReservationManager::removeReservationForBook(const std::string& bookTitle) {
    for (size_t index = 0; index < managedReservations.size(); ++index) {
        if (managedReservations[index].associatedBook.getPublicationTitle() == bookTitle) {
            managedReservations.erase(managedReservations.begin() + index);
            return;
        }
    }
}

Reservation ReservationManager::findReservationByBook(const std::string& bookTitle) const {
    for (size_t index = 0; index < managedReservations.size(); ++index) {
        if (managedReservations[index].associatedBook.getPublicationTitle() == bookTitle) {
            return managedReservations[index];
        }
    }
    LibraryExceptions::throwReservationFailed("Бронирование не найдено");
    return Reservation(Book("", "", 0), Member("", 0));
}