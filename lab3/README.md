# README: Система Управления Библиотекой (Library Management System)

- Классы: 50
- Поля: 150
- Уникальные поведения: 100 
- Ассоциации: 30
- Исключения: 13 
  
## Исключения (13)
Все в классе LibraryExceptions (статические методы для throw):
- throwAccessDenied("Ошибка доступа")
- throwBookNotFound("Книга не найдена")
- throwDuplicateBook("Дубликат книги")
- throwInvalidAuthor("Некорректный автор")
- throwInvalidCategory("Некорректная категория")
- throwInvalidLoan("Некорректный заём")
- throwInvalidMember("Некорректный участник")
- throwInvalidPublisher("Некорректный издатель")
- throwLibraryFull("Библиотека переполнена")
- throwMemberNotFound("Участник не найден")
- throwOverdueBook("Книга просрочена")
- throwPaymentFailed("Оплата не удалась")
- throwReservationFailed("Бронирование не удалось")

## Классы
Формат: Класс Поля Методы → Ассоциации (классы как поля/параметры)

Publication 2 2 → Book, AudioBook, EBook, Journal, Magazine
- Поля: publicationTitle, publicationAuthor
- Методы: getPublicationTitle, getAuthorName

Book 2 2 → Publication, Borrower, BookManager, Category, Genre, Shelf, Loan, Reservation, SearchService, Librarian, CatalogSystem, BookCopy, Donation
- Поля: totalPagesCount, bookmarkedPageNumber
- Методы: openToPage, bookmarkPage

AudioBook 1 3 → Publication
- Поля: audioDurationInMinutes
- Методы: playSample, adjustVolume, openToPage

EBook 1 3 → Publication, DigitalLibrary
- Поля: fileFormatType
- Методы: download, zoomIn, openToPage

Journal 1 3 → Publication
- Поля: journalIssueNumber
- Методы: citeArticle, archiveIssue, openToPage

Magazine 1 3 → Publication
- Поля: magazineIssueMonth
- Методы: flipToPage, subscribe, openToPage

Author 2 2 → Book
- Поля: authorFullName, writtenBooksList
- Методы: addWrittenBook, getWrittenBooks

Publisher 2 2 → Book
- Поля: publisherCompanyName, publishedBooksList
- Методы: publishBook, validatePublisher

Category 2 2 → Book
- Поля: categoryDescription, booksInCategory
- Методы: assignBookToCategory, validateCategory

Genre 2 2 → Book
- Поля: genreDescription, booksInGenre
- Методы: addBookToGenre, listBooksInGenre

Shelf 2 3 → Book, Room, Branch
- Поля: booksOnShelf, shelfCapacity
- Методы: addBookToShelf, removeBookFromShelf, getShelfCapacity

Room 2 2 → Shelf, ReadingRoom, EventRoom, ArchiveRoom
- Поля: roomDescription, shelvesInRoom
- Методы: addShelfToRoom, cleanRoom

Branch 2 2 → Shelf, Library
- Поля: branchLocationName, shelvesInBranch
- Методы: addShelfToBranch, organizeShelves

Library 3 2 → Branch
- Поля: mainLibraryName, libraryBranches, maxBranchesAllowed
- Методы: addBranchToLibrary, checkCapacity

Member 3 2 → Borrower, VIPMember, Loan, Reservation, NotificationService, Librarian, MemberManager
- Поля: memberFullName, membershipId, isActiveMember
- Методы: renewMembership, updateMembershipStatus

Borrower 1 2 → Member, Book
- Поля: borrowedBooksList
- Методы: borrowBook, returnBook

VIPMember 1 2 → Member
- Поля: priorityLevel
- Методы: accessPremiumContent, requestPriorityLoan

Staff 3 2 → Librarian
- Поля: staffFullName, employeeIdentification, isOnDuty
- Методы: clockIn, clockOut

Librarian 1 2 → Staff, Book, Member
- Поля: issuedBooksCount
- Методы: issueBookToMember, collectFineFromMember

Loan 3 2 → Book, Member
- Поля: associatedBook, associatedMember, loanDueDate
- Методы: extendDueDate, validateLoan

Reservation 3 2 → Book, Member
- Поля: associatedBook, associatedMember, isConfirmed
- Методы: confirmReservation, cancelReservation

BookManager 1 3 → Book
- Поля: managedBooksCollection
- Методы: addBookToCollection, removeBookFromCollection, findBookByTitle

MemberManager 1 3 → Member
- Поля: managedMembers
- Методы: addMemberToRecords, removeMemberFromRecords, findMemberById

LoanManager 1 3 → Loan
- Поля: managedLoans
- Методы: addLoanToRecords, removeLoanFromRecords, findLoanByBook

ReservationManager 1 3 → Reservation
- Поля: managedReservations
- Методы: addReservationToRecords, removeReservationForBook, findReservationByBook

SearchService 1 3 → Book
- Поля: indexedBooks
- Методы: indexBook, searchByTitle, searchByAuthor

NotificationService 1 2 → Member
- Поля: notificationLog
- Методы: sendOverdueNotification, sendReservationConfirmation

FineCalculator 1 3
- Поля: currentFineAmount
- Методы: calculateFine, resetFine, getCurrentFine

CatalogSystem 1 3 → Book
- Поля: catalogedBooks
- Методы: registerBook, updateBookStatus, getAllBooks

DigitalLibrary 1 3 → EBook
- Поля: digitalCollection
- Методы: uploadEBook, removeEBook, getEBook

ReadingRoom 1 2 → Room
- Поля: occupiedSeatsCount
- Методы: assignSeat, freeSeat

EventRoom 1 2 → Room
- Поля: currentEventName
- Методы: scheduleEvent, cancelEvent

ArchiveRoom 1 2 → Room
- Поля: isSecured
- Методы: secureDocuments, logAccess

BookCopy 3 2 → Book
- Поля: originalBookReference, copyIdentification, isAvailable
- Методы: markAsAvailable, markAsBorrowed

FineRecord 3 2
- Поля: memberIdentification, fineAmount, isPaidStatus
- Методы: markAsPaid, isPaid

Event 2 2
- Поля: eventName, eventDate
- Методы: changeDate, getEventDate

Seat 2 2
- Поля: seatNumber, isOccupied
- Методы: occupy, free

DigitalDevice 3 2
- Поля: deviceIdentification, isConnected, currentUser
- Методы: connect, disconnect

ReportGenerator 2 2
- Поля: reportType, generatedData
- Методы: generateReport, saveReport

BackupSystem 2 2
- Поля: lastBackupTime, storagePath
- Методы: createBackup, restoreFromBackup

UserSession 3 2
- Поля: sessionIdentification, startTime, isActive
- Методы: start, end

AuditLog 1 2
- Поля: logEntries
- Методы: logAction, clearLog

Printer 3 2
- Поля: printerName, isOnline, paperLevel
- Методы: printDocument, checkPaper

SecurityCamera 3 2
- Поля: cameraIdentification, cameraLocation, isRecording
- Методы: startRecording, stopRecording

AccessCard 3 2
- Поля: cardIdentification, ownerName, isActive
- Методы: activate, deactivate

InventoryItem 3 2
- Поля: itemIdentification, itemName, currentQuantity
- Методы: addStock, removeStock

MaintenanceSchedule 1 2
- Поля: taskList
- Методы: addTask, completeTask

Visitor 3 2
- Поля: visitorName, visitPurpose, entryTime
- Методы: recordEntry, recordExit

Donation 3 2 → Book
- Поля: donorName, donationAmount, donatedBooks
- Методы: addBook, processDonation

LibraryCard 3 2
- Поля: cardNumber, issueDate, expiryDate
- Методы: renew, block
