#pragma once
#include <string>

class ReportGenerator {
public:
    void generateReport(const std::string& type);
    void saveReport(const std::string& filename);

private:
    std::string reportType;
    std::string generatedData;
};