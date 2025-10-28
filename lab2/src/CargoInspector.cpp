#include "../include/CargoInspector.h"

CargoInspector::CargoInspector(std::string inspectorId) : inspectorId(inspectorId) {}

std::string CargoInspector::getInspectorId()
{
    return inspectorId;
}
bool CargoInspector::inspectCargo(Freight *freight)
{
    bool isValid = freight->getWeight() > 0 && !freight->isHazardous();
    if (isValid)
    {
        std::cout << "Груз " << freight->getFreightId() << " прошёл проверку: " << inspectorId << std::endl;
    }
    else
    {
        std::cout << "Груз " << freight->getFreightId() << " не прошёл проверку: " << inspectorId << std::endl;
    }
    return isValid;
}