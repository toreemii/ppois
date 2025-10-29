#include "Reservation.h"
#include "LibraryExceptions.h"

Reservation::Reservation(Book &reservedBook, Member &reservingMember)
    : associatedBook(reservedBook), associatedMember(reservingMember), isConfirmed(false) {}

void Reservation::confirmReservation()
{
    if (isConfirmed)
    {
        LibraryExceptions::throwReservationFailed("Уже подтверждено");
    }
    isConfirmed = true;
}

void Reservation::cancelReservation()
{
    if (isConfirmed)
    {
        isConfirmed = false;
    }
}

Book &Reservation::getAssociatedBook()
{
    return associatedBook;
}

Member &Reservation::getAssociatedMember()
{
    return associatedMember;
}