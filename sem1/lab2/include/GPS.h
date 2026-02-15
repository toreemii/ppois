#pragma once
#include <tuple>
#include "Route.h"

class GPS
{
private:
    double longitude;
    double latitude;

public:
    GPS(double longitude, double latitude);
    GPS() {}
    std::tuple<double, double> getCoordinates();
    void setCoordinates(double longitude, double latitude);
    std::tuple<int, int> chooseRoute(double maxSpeed, Route *route);
};