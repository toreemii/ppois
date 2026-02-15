#pragma once
#include <string>
class License
{
private:
    std::string licenseId;
    std::string licenseType;
    std::string licenseStatus;

public:
    License(std::string licenseId, std::string licenseType, std::string licenseStatus);
    License();
    std::string getLicenseId();
    void setLicenseId(std::string licenseId);
    std::string getLicenseType();
    void setLicenseType(std::string licenseType);
    std::string getLicenseStatus();
    void setLicenseStatus(std::string licenseStatus);
};