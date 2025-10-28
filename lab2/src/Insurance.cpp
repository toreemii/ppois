#include "../include/Insurance.h"

Insurance::Insurance(std::string insuranceId, double coverageAmount) : insuranceId(insuranceId), coverageAmount(coverageAmount) {}

std::string Insurance::getInsuranceId()
{
    return insuranceId;
}
void Insurance::insureFreight(Freight *freight)
{
    std::cout << "Груз " << freight->getFreightId() << " застрахован на сумму " << coverageAmount << ": " << insuranceId << std::endl;
}
void Insurance::insureVehicle(Vehicle *vehicle)
{
    std::cout << "Транспорт застрахован на сумму " << coverageAmount << ": " << insuranceId << std::endl;
}
