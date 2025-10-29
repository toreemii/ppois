#include "Printer.h"
#include <iostream>

Printer::Printer(const std::string& name)
    : printerName(name), isOnline(true), paperLevel(100) {}

void Printer::printDocument(const std::string& content) {
    if (isOnline && paperLevel > 0) {
        std::cout << "Печать: " << content << std::endl;
        paperLevel -= 1;
    }
}

void Printer::checkPaper() {
    std::cout << "Бумаги осталось: " << paperLevel << std::endl;
}