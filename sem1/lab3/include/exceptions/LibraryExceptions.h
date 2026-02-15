#pragma once
#include <exception>
#include <string>

class LibraryExceptions : public std::exception {
public:
    static void throwAccessDenied(const std::string& message);
    static void throwBookNotFound(const std::string& message);
    static void throwDuplicateBook(const std::string& message);
    static void throwInvalidAuthor(const std::string& message);
    static void throwInvalidCategory(const std::string& message);
    static void throwInvalidLoan(const std::string& message);
    static void throwInvalidMember(const std::string& message);
    static void throwInvalidPublisher(const std::string& message);
    static void throwLibraryFull(const std::string& message);
    static void throwMemberNotFound(const std::string& message);
    static void throwOverdueBook(const std::string& message);
    static void throwPaymentFailed(const std::string& message);
    static void throwReservationFailed(const std::string& message);

private:
    LibraryExceptions(const std::string& message);
    std::string errorMessage;
    const char* what() const noexcept override;
};