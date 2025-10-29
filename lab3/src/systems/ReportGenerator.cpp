#include "ReportGenerator.h"
#include <iostream>

void ReportGenerator::generateReport(const std::string& type) {
    reportType = type;
    generatedData = "Данные отчёта";
    std::cout << "Отчёт сгенерирован" << std::endl;
}

void ReportGenerator::saveReport(const std::string& filename) {
    if (!filename.empty()) {
        std::cout << "Отчёт сохранён как " << filename << std::endl;
    }
}