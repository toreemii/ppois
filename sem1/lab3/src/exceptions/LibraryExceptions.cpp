#include "LibraryExceptions.h"

LibraryExceptions::LibraryExceptions(const std::string& message) : errorMessage(message) {}

const char* LibraryExceptions::what() const noexcept {
    return errorMessage.c_str();
}

void LibraryExceptions::throwAccessDenied(const std::string& message) {
    throw LibraryExceptions("Ошибка доступа: " + message);
}

void LibraryExceptions::throwBookNotFound(const std::string& message) {
    throw LibraryExceptions("Книга не найдена: " + message);
}

void LibraryExceptions::throwDuplicateBook(const std::string& message) {
    throw LibraryExceptions("Дубликат книги: " + message);
}

void LibraryExceptions::throwInvalidAuthor(const std::string& message) {
    throw LibraryExceptions("Некорректный автор: " + message);
}

void LibraryExceptions::throwInvalidCategory(const std::string& message) {
    throw LibraryExceptions("Некорректная категория: " + message);
}

void LibraryExceptions::throwInvalidLoan(const std::string& message) {
    throw LibraryExceptions("Некорректный заём: " + message);
}

void LibraryExceptions::throwInvalidMember(const std::string& message) {
    throw LibraryExceptions("Некорректный участник: " + message);
}

void LibraryExceptions::throwInvalidPublisher(const std::string& message) {
    throw LibraryExceptions("Некорректный издатель: " + message);
}

void LibraryExceptions::throwLibraryFull(const std::string& message) {
    throw LibraryExceptions("Библиотека переполнена: " + message);
}

void LibraryExceptions::throwMemberNotFound(const std::string& message) {
    throw LibraryExceptions("Участник не найден: " + message);
}

void LibraryExceptions::throwOverdueBook(const std::string& message) {
    throw LibraryExceptions("Книга просрочена: " + message);
}

void LibraryExceptions::throwPaymentFailed(const std::string& message) {
    throw LibraryExceptions("Оплата не удалась: " + message);
}

void LibraryExceptions::throwReservationFailed(const std::string& message) {
    throw LibraryExceptions("Бронирование не удалось: " + message);
}