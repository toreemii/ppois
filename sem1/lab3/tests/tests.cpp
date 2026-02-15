#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include "../include/books/Publication.h"
#include "../include/books/Book.h"
#include "../include/books/AudioBook.h"
#include "../include/books/EBook.h"
#include "../include/books/Journal.h"
#include "../include/books/Magazine.h"
#include "../include/members/Author.h"
#include "../include/members/Publisher.h"
#include "../include/books/Category.h"
#include "../include/books/Genre.h"
#include "../include/stuff/Shelf.h"
#include "../include/rooms/Room.h"
#include "../include/library/Branch.h"
#include "..//include/library/Library.h"
#include "../include/members/Member.h"
#include "../include/members/Borrower.h"
#include "../include/members/VIPMember.h"
#include "../include/stuff/Staff.h"
#include "../include/members/Librarian.h"
#include "../include/service/Loan.h"
#include "../include/service/Reservation.h"
#include "../include/members/BookManager.h"
#include "../include/members/MemberManager.h"
#include "../include/members/LoanManager.h"
#include "../include/members/ReservationManager.h"
#include "../include/service/SearchService.h"
#include "../include/service/NotificationService.h"
#include "../include/service/FineCalculator.h"
#include "../include/systems/CatalogSystem.h"
#include "../include/books/DigitalLibrary.h"
#include "../include/rooms/ReadingRoom.h"
#include "../include/rooms/EventRoom.h"
#include "../include/rooms/ArchiveRoom.h"
#include "../include/books/BookCopy.h"
#include "../include/service/FineRecord.h"
#include "../include/library/Event.h"
#include "../include/stuff/Seat.h"
#include "../include/systems/DigitalDevice.h"
#include "../include/systems/ReportGenerator.h"
#include "../include/systems/BackupSystem.h"
#include "../include/library/UserSession.h"
#include "../include/service/AuditLog.h"
#include "../include/systems/Printer.h"
#include "../include/security/SecurityCamera.h"
#include "../include/service/AccessCard.h"
#include "../include/stuff/InventoryItem.h"
#include "../include/library/MaintenanceSchedule.h"
#include "../include/members/Visitor.h"
#include "../include/service/Donation.h"
#include "../include/service/LibraryCard.h"
#include "../include/exceptions/LibraryExceptions.h"

TEST(AudioBookTest, PlaySampleAndVolume)
{
    AudioBook ab("Audio Story", "Narrator", 120);
    std::ostringstream oss;
    std::streambuf *cout_buffer = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    ab.playSample();
    ab.adjustVolume(75);
    std::cout.rdbuf(cout_buffer);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("Проигрывание образца") != std::string::npos);
    EXPECT_TRUE(output.find("Громкость установлена на 75") != std::string::npos);
}

TEST(EBookTest, DownloadAndZoom)
{
    EBook eb("Digital Book", "E-Author", "PDF");
    std::ostringstream oss;
    std::streambuf *cout_buffer = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    eb.download();
    eb.zoomIn();
    std::cout.rdbuf(cout_buffer);
    EXPECT_TRUE(oss.str().find("Скачивание") != std::string::npos);
}

TEST(JournalTest, CiteAndArchive)
{
    Journal j("Science", "Editor", 5);
    std::ostringstream oss;
    std::streambuf *cout_buffer = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    j.citeArticle();
    j.archiveIssue();
    std::cout.rdbuf(cout_buffer);
    EXPECT_TRUE(oss.str().find("Цитирование") != std::string::npos);
}

TEST(MagazineTest, FlipAndSubscribe)
{
    Magazine m("Fashion", "Editor", 3);
    std::ostringstream oss;
    std::streambuf *cout_buffer = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    m.flipToPage(20);
    m.subscribe();
    std::cout.rdbuf(cout_buffer);
    EXPECT_TRUE(oss.str().find("Перелистнуто") != std::string::npos);
}

TEST(AuthorTest, AddBook)
{
    Author author("Leo Tolstoy");
    Book book("War and Peace", "Leo Tolstoy", 1200);
    author.addWrittenBook(book);
    auto books = author.getWrittenBooks();
    EXPECT_EQ(books.size(), 1);
    EXPECT_EQ(books[0].getPublicationTitle(), "War and Peace");
}

TEST(AuthorTest, InvalidBookTitleThrows)
{
    Author author("Author");
    Book invalid("", "Author", 100);
    EXPECT_THROW(author.addWrittenBook(invalid), LibraryExceptions);
}

TEST(PublisherTest, ValidatePublisher)
{
    Publisher p("Good Press");
    p.validatePublisher();
    SUCCEED();
}

TEST(PublisherTest, EmptyNameThrows)
{
    Publisher p("");
    EXPECT_THROW(p.validatePublisher(), LibraryExceptions);
}

TEST(CategoryTest, ValidateCategory)
{
    Category c("Fiction");
    c.validateCategory();
    SUCCEED();
}

TEST(CategoryTest, EmptyThrows)
{
    Category c("");
    EXPECT_THROW(c.validateCategory(), LibraryExceptions);
}

TEST(GenreTest, ListBooks)
{
    Genre g("Fantasy");
    Book b1("LOTR", "Tolkien", 400);
    Book b2("HP", "Rowling", 300);
    g.addBookToGenre(b1);
    g.addBookToGenre(b2);
    std::ostringstream oss;
    std::streambuf *cout_buffer = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    g.listBooksInGenre();
    std::cout.rdbuf(cout_buffer);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("LOTR") != std::string::npos);
    EXPECT_TRUE(output.find("HP") != std::string::npos);
}

TEST(ShelfTest, AddAndRemoveBook)
{
    Shelf shelf(2);
    Book b1("Book1", "A", 100);
    Book b2("Book2", "B", 200);
    shelf.addBookToShelf(b1);
    shelf.addBookToShelf(b2);
    shelf.removeBookFromShelf("Book1");
    SUCCEED();
}

TEST(ShelfTest, FullShelfThrows)
{
    Shelf shelf(1);
    Book b1("B1", "A", 100);
    Book b2("B2", "B", 200);
    shelf.addBookToShelf(b1);
    EXPECT_THROW(shelf.addBookToShelf(b2), LibraryExceptions);
}

TEST(RoomTest, AddShelf)
{
    Room room("Main");
    Shelf shelf(10);
    room.addShelfToRoom(shelf);
    SUCCEED();
}

TEST(BranchTest, OrganizeShelves)
{
    Branch branch("Central");
    Shelf s1(5), s2(10), s3(3);
    branch.addShelfToBranch(s1);
    branch.addShelfToBranch(s2);
    branch.addShelfToBranch(s3);
    branch.organizeShelves();
    SUCCEED();
}

TEST(LibraryTest, AddBranch)
{
    Library lib("City");
    Branch b1("North"), b2("South");
    lib.addBranchToLibrary(b1);
    lib.addBranchToLibrary(b2);
    SUCCEED();
}

TEST(LibraryTest, FullLibraryThrows)
{
    Library lib("Small");
    Branch b("B");
    for (int i = 0; i < 5; ++i)
    {
        Branch temp("Temp" + std::to_string(i));
        lib.addBranchToLibrary(temp);
    }
    EXPECT_THROW(lib.addBranchToLibrary(b), LibraryExceptions);
}

TEST(MemberTest, UpdateStatus)
{
    Member m("Alice", 123);
    m.updateMembershipStatus();
    SUCCEED();
}

TEST(MemberTest, InvalidIdThrows)
{
    Member m("Bob", 0);
    EXPECT_THROW(m.updateMembershipStatus(), LibraryExceptions);
}

TEST(BorrowerTest, BorrowAndReturn)
{
    Borrower borrower("Charlie", 789);
    Book book("C++", "Stroustrup", 800);
    borrower.borrowBook(book);
    borrower.returnBook("C++");
    SUCCEED();
}

TEST(VIPMemberTest, PremiumAccess)
{
    VIPMember vip("VIP", 1);
    std::ostringstream oss;
    std::streambuf *cout_buffer = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    vip.accessPremiumContent();
    vip.requestPriorityLoan();
    std::cout.rdbuf(cout_buffer);
    EXPECT_TRUE(oss.str().find("Доступ к премиум") != std::string::npos);
}

TEST(StaffTest, ClockInOut)
{
    Staff s("Librarian", 101);
    s.clockIn();
    s.clockOut();
    SUCCEED();
}

TEST(LibrarianTest, IssueAndFine)
{
    Librarian lib("Anna", 102);
    Book book("Math", "Prof", 200);
    Member member("Student", 201);
    lib.issueBookToMember(book, member);
    lib.collectFineFromMember(member, 50.0);
    SUCCEED();
}

TEST(LoanTest, ExtendAndValidate)
{
    Book b("LoanBook", "A", 100);
    Member m("Borrower", 1);
    Loan loan(b, m, "2025-12-01");
    loan.extendDueDate("2026-01-01");
    loan.validateLoan();
    SUCCEED();
}

TEST(LoanTest, EmptyDateThrows)
{
    Book b("B", "A", 100);
    Member m("M", 1);
    Loan loan(b, m, "");
    EXPECT_THROW(loan.validateLoan(), LibraryExceptions);
}

TEST(ReservationTest, ConfirmCancel)
{
    Book b("ResBook", "A", 100);
    Member m("User", 1);
    Reservation r(b, m);
    r.confirmReservation();
    EXPECT_THROW(r.confirmReservation(), LibraryExceptions);
    r.cancelReservation();
    SUCCEED();
}

TEST(BookManagerTest, AddFindRemove)
{
    BookManager bm;
    Book b1("Unique", "A", 100);
    bm.addBookToCollection(b1);
    auto found = bm.findBookByTitle("Unique");
    EXPECT_EQ(found.getPublicationTitle(), "Unique");
    bm.removeBookFromCollection("Unique");
    EXPECT_THROW(bm.findBookByTitle("Unique"), LibraryExceptions);
}

TEST(BookManagerTest, DuplicateThrows)
{
    BookManager bm;
    Book b("Same", "A", 100);
    bm.addBookToCollection(b);
    EXPECT_THROW(bm.addBookToCollection(b), LibraryExceptions);
}

TEST(LoanManagerTest, AddFindRemove)
{
    LoanManager lm;
    Book b("LBook", "A", 100);
    Member m("M", 1);
    Loan loan(b, m, "2025");
    lm.addLoanToRecords(loan);
    auto found = lm.findLoanByBook("LBook");
    lm.removeLoanFromRecords("LBook");
    EXPECT_THROW(lm.findLoanByBook("LBook"), LibraryExceptions);
}

TEST(ReservationManagerTest, AddFindRemove)
{
    ReservationManager rm;
    Book b("RBook", "A", 100);
    Member m("M", 1);
    Reservation r(b, m);
    rm.addReservationToRecords(r);
    auto found = rm.findReservationByBook("RBook");
    rm.removeReservationForBook("RBook");
    EXPECT_THROW(rm.findReservationByBook("RBook"), LibraryExceptions);
}

TEST(SearchServiceTest, SearchByTitleAuthor)
{
    SearchService ss;
    Book b1("C++ Programming", "Bjarne", 700);
    Book b2("Java Guide", "Oracle", 500);
    ss.indexBook(b1);
    ss.indexBook(b2);
    auto byTitle = ss.searchByTitle("C++");
    EXPECT_EQ(byTitle.size(), 1);
    auto byAuthor = ss.searchByAuthor("Bjarne");
    EXPECT_EQ(byAuthor.size(), 1);
    EXPECT_THROW(ss.searchByTitle("Python"), LibraryExceptions);
}

TEST(NotificationServiceTest, SendNotifications)
{
    NotificationService ns;
    Member m("User", 1);
    std::ostringstream oss;
    std::streambuf *cout_buffer = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    ns.sendOverdueNotification(m, "Overdue!");
    ns.sendReservationConfirmation(m, "Confirmed!");
    std::cout.rdbuf(cout_buffer);
    EXPECT_TRUE(oss.str().find("Отправлено") != std::string::npos);
}

TEST(FineCalculatorTest, CalculateAndReset)
{
    FineCalculator fc;
    double fine = fc.calculateFine(5);
    EXPECT_EQ(fine, 50.0);
    fc.resetFine();
    EXPECT_EQ(fc.getCurrentFine(), 0.0);
}

TEST(CatalogSystemTest, RegisterAndGet)
{
    CatalogSystem cs;
    Book b("CatBook", "A", 100);
    cs.registerBook(b);
    auto all = cs.getAllBooks();
    EXPECT_EQ(all.size(), 1);
}

TEST(DigitalLibraryTest, UploadGetRemove)
{
    DigitalLibrary dl;
    EBook eb("EBook", "A", "EPUB");
    dl.uploadEBook(eb);
    auto got = dl.getEBook("EBook");
    dl.removeEBook("EBook");
    EXPECT_THROW(dl.getEBook("EBook"), LibraryExceptions);
}

TEST(ReadingRoomTest, SeatManagement)
{
    ReadingRoom rr;
    std::ostringstream oss;
    std::streambuf *cout_buffer = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    rr.assignSeat(5);
    rr.freeSeat(5);
    std::cout.rdbuf(cout_buffer);
    EXPECT_TRUE(oss.str().find("занято") != std::string::npos);
}

TEST(EventRoomTest, ScheduleCancel)
{
    EventRoom er;
    std::ostringstream oss;
    std::streambuf *cout_buffer = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    er.scheduleEvent("Lecture");
    er.cancelEvent();
    std::cout.rdbuf(cout_buffer);
    EXPECT_TRUE(oss.str().find("запланировано") != std::string::npos);
}

TEST(ArchiveRoomTest, SecureAndLog)
{
    ArchiveRoom ar;
    std::ostringstream oss;
    std::streambuf *cout_buffer = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    ar.secureDocuments();
    ar.logAccess();
    std::cout.rdbuf(cout_buffer);
    EXPECT_TRUE(oss.str().find("защищены") != std::string::npos);
}

TEST(BookCopyTest, Availability)
{
    Book original("Orig", "A", 100);
    BookCopy copy(original, 1);
    copy.markAsBorrowed();
    copy.markAsAvailable();
    SUCCEED();
}

TEST(FineRecordTest, Payment)
{
    FineRecord fr(1, 30.0);
    EXPECT_FALSE(fr.isPaid());
    fr.markAsPaid();
    EXPECT_TRUE(fr.isPaid());
}

TEST(EventTest, ChangeDate)
{
    Event e("Seminar", "2025-01-01");
    e.changeDate("2025-02-01");
    EXPECT_EQ(e.getEventDate(), "2025-02-01");
}

TEST(SeatTest, OccupyFree)
{
    Seat s(10);
    s.occupy();
    s.free();
    SUCCEED();
}

TEST(DigitalDeviceTest, ConnectDisconnect)
{
    DigitalDevice dd(1);
    dd.connect();
    dd.disconnect();
    SUCCEED();
}

TEST(ReportGeneratorTest, GenerateSave)
{
    ReportGenerator rg;
    std::ostringstream oss;
    std::streambuf *cout_buffer = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    rg.generateReport("Monthly");
    rg.saveReport("report.txt");
    std::cout.rdbuf(cout_buffer);
    EXPECT_TRUE(oss.str().find("сгенерирован") != std::string::npos);
}

TEST(BackupSystemTest, CreateRestore)
{
    BackupSystem bs;
    std::ostringstream oss;
    std::streambuf *cout_buffer = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    bs.createBackup();
    bs.restoreFromBackup("yesterday");
    std::cout.rdbuf(cout_buffer);
    EXPECT_TRUE(oss.str().find("создана") != std::string::npos);
}

TEST(UserSessionTest, StartEnd)
{
    UserSession us(1);
    us.start();
    us.end();
    SUCCEED();
}

TEST(AuditLogTest, LogAndClear)
{
    AuditLog al;
    al.logAction("Login");
    al.clearLog();
    SUCCEED();
}

TEST(PrinterTest, PrintAndCheck)
{
    Printer p("HP");
    std::ostringstream oss;
    std::streambuf *cout_buffer = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    p.printDocument("Doc");
    p.checkPaper();
    std::cout.rdbuf(cout_buffer);
    EXPECT_TRUE(oss.str().find("Печать") != std::string::npos);
}

TEST(SecurityCameraTest, RecordControl)
{
    SecurityCamera sc(1, "Lobby");
    sc.startRecording();
    sc.stopRecording();
    SUCCEED();
}

TEST(AccessCardTest, ActivateDeactivate)
{
    AccessCard ac(100, "Staff");
    ac.deactivate();
    ac.activate();
    SUCCEED();
}

TEST(InventoryItemTest, StockManagement)
{
    InventoryItem ii(1, "Pen", 50);
    ii.addStock(10);
    ii.removeStock(5);
    SUCCEED();
}

TEST(MaintenanceScheduleTest, TaskManagement)
{
    MaintenanceSchedule ms;
    ms.addTask("Clean");
    ms.completeTask("Clean");
    SUCCEED();
}

TEST(VisitorTest, EntryExit)
{
    Visitor v("Guest", "Tour");
    v.recordEntry();
    v.recordExit();
    SUCCEED();
}

TEST(DonationTest, Process)
{
    Donation d("Donor", 100.0);
    Book b("Gift", "A", 100);
    d.addBook(b);
    d.processDonation();
    SUCCEED();
}

TEST(LibraryCardTest, RenewBlock)
{
    LibraryCard lc(500, "2025");
    lc.renew();
    lc.block();
    SUCCEED();
}

TEST(MemberManagerTest, AddMemberToRecords)
{
    MemberManager mm;
    Member member("John Doe", 123);
    mm.addMemberToRecords(member);
    Member found = mm.findMemberById(123);
    EXPECT_EQ(found.getMemberShipId(), 123);
    EXPECT_EQ(found.getMemberFullName(), "John Doe");
}

TEST(MemberManagerTest, RemoveMemberFromRecords)
{
    MemberManager mm;
    Member member1("Alice", 1);
    Member member2("Bob", 2);
    mm.addMemberToRecords(member1);
    mm.addMemberToRecords(member2);
    mm.removeMemberFromRecords(1);
    EXPECT_THROW(mm.findMemberById(1), LibraryExceptions);
    Member found = mm.findMemberById(2);
    EXPECT_EQ(found.getMemberShipId(), 2);
    EXPECT_EQ(found.getMemberFullName(), "Bob");
}

TEST(MemberManagerTest, RemoveNonExistentMember)
{
    MemberManager mm;
    Member member("Test", 999);
    mm.addMemberToRecords(member);
    EXPECT_NO_THROW(mm.removeMemberFromRecords(888));
    EXPECT_NO_THROW({
        Member found = mm.findMemberById(999);
        EXPECT_EQ(found.getMemberShipId(), 999);
    });
}

TEST(MemberManagerTest, FindMemberByIdSuccess)
{
    MemberManager mm;
    Member member("Jane Smith", 456);
    mm.addMemberToRecords(member);
    Member found = mm.findMemberById(456);
    EXPECT_EQ(found.getMemberShipId(), 456);
    EXPECT_EQ(found.getMemberFullName(), "Jane Smith");
}

TEST(MemberManagerTest, FindMemberByIdNotFound)
{
    MemberManager mm;
    Member member("Some Member", 111);
    mm.addMemberToRecords(member);
    EXPECT_THROW(mm.findMemberById(999), LibraryExceptions);
}

TEST(MemberManagerTest, MultipleMembersManagement)
{
    MemberManager mm;
    for (int i = 1; i <= 5; ++i)
    {
        Member member("Member " + std::to_string(i), i);
        mm.addMemberToRecords(member);
    }
    mm.removeMemberFromRecords(2);
    mm.removeMemberFromRecords(4);
    EXPECT_NO_THROW({
        Member found1 = mm.findMemberById(1);
        EXPECT_EQ(found1.getMemberFullName(), "Member 1");
    });
    EXPECT_THROW(mm.findMemberById(2), LibraryExceptions);
    EXPECT_NO_THROW({
        Member found3 = mm.findMemberById(3);
        EXPECT_EQ(found3.getMemberFullName(), "Member 3");
    });
    EXPECT_THROW(mm.findMemberById(4), LibraryExceptions);
    EXPECT_NO_THROW({
        Member found5 = mm.findMemberById(5);
        EXPECT_EQ(found5.getMemberFullName(), "Member 5");
    });
}

TEST(MemberManagerTest, EmptyManagerOperations)
{
    MemberManager mm;
    EXPECT_THROW(mm.findMemberById(1), LibraryExceptions);
    EXPECT_NO_THROW(mm.removeMemberFromRecords(1));
}

TEST(MemberManagerTest, AddMembersWithSameId)
{
    MemberManager mm;
    Member member1("First Member", 100);
    Member member2("Second Member", 100);
    mm.addMemberToRecords(member1);
    mm.addMemberToRecords(member2);
    Member found = mm.findMemberById(100);
    EXPECT_EQ(found.getMemberShipId(), 100);
    EXPECT_EQ(found.getMemberFullName(), "First Member");
}

TEST(MemberManagerTest, RemoveLastMember)
{
    MemberManager mm;
    Member member("Last Member", 777);
    mm.addMemberToRecords(member);
    mm.removeMemberFromRecords(777);
    EXPECT_THROW(mm.findMemberById(777), LibraryExceptions);
}

TEST(MemberManagerTest, FindAfterMultipleRemovals)
{
    MemberManager mm;
    Member m1("One", 1);
    Member m2("Two", 2);
    Member m3("Three", 3);
    Member m4("Four", 4);
    mm.addMemberToRecords(m1);
    mm.addMemberToRecords(m2);
    mm.addMemberToRecords(m3);
    mm.addMemberToRecords(m4);
    mm.removeMemberFromRecords(2);
    mm.removeMemberFromRecords(4);
    EXPECT_NO_THROW(mm.findMemberById(1));
    EXPECT_NO_THROW(mm.findMemberById(3));
    EXPECT_THROW(mm.findMemberById(2), LibraryExceptions);
    EXPECT_THROW(mm.findMemberById(4), LibraryExceptions);
}

TEST(MemberTest, ConstructorAndGetters)
{
    Member member("Test User", 123);
    EXPECT_EQ(member.getMemberShipId(), 123);
    EXPECT_EQ(member.getMemberFullName(), "Test User");
}

TEST(MemberTest, RenewMembership)
{
    Member member("Test", 1);
    EXPECT_NO_THROW(member.renewMembership());
}

TEST(MemberTest, UpdateMembershipStatusValid)
{
    Member member("Valid Member", 123);
    EXPECT_NO_THROW(member.updateMembershipStatus());
}

TEST(MemberTest, UpdateMembershipStatusInvalid)
{
    Member member("Invalid Member", 0);
    EXPECT_THROW(member.updateMembershipStatus(), LibraryExceptions);
}

TEST(MemberTest, UpdateMembershipStatusNegative)
{
    Member member("Negative Member", -5);
    EXPECT_THROW(member.updateMembershipStatus(), LibraryExceptions);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}