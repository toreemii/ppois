#pragma once
#include <string>
#include "Freight.h"

class CargoInspector
{
private:
    std::string inspectorId;

public:
    CargoInspector(std::string inspectorId);
    bool inspectCargo(Freight *freight);
    std::string getInspectorId();
};