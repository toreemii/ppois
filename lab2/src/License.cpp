#include "../include/License.h"

License::License(std::string licenseId, std::string licenseType, std::string licenseStatus)
    : licenseId(licenseId), licenseType(licenseType), licenseStatus(licenseStatus) {}

License::License() : licenseId(""), licenseType(""), licenseStatus("") {}

std::string License::getLicenseId()
{
    return licenseId;
}
void License::setLicenseId(std::string licenseId)
{
    this->licenseId = licenseId;
}
std::string License::getLicenseType()
{
    return licenseType;
}
void License::setLicenseType(std::string licenseType)
{
    this->licenseType = licenseType;
}
std::string License::getLicenseStatus()
{
    return licenseStatus;
}
void License::setLicenseStatus(std::string licenseStatus)
{
    this->licenseStatus = licenseStatus;
}
