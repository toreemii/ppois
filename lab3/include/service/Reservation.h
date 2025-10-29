#pragma once
#include "Book.h"
#include "Member.h"

class Reservation
{
public:
    Reservation(Book &reservedBook, Member &reservingMember);
    void confirmReservation();
    void cancelReservation();
    Book &getAssociatedBook();
    Member& getAssociatedMember();

private:
    Book &associatedBook;
    Member &associatedMember;
    bool isConfirmed;
};