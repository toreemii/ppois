#pragma once
#include <string>
class Printer {
public:
    Printer(const std::string& name);
    void printDocument(const std::string& content);
    void checkPaper();

private:
    std::string printerName;
    bool isOnline;
    int paperLevel;
};