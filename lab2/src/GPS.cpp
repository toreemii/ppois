#include "../include/GPS.h"
#include <iostream>

GPS::GPS(double longitude, double latitude) : longitude(longitude), latitude(latitude) {}

std::tuple<double, double> GPS::getCoordinates()
{
    return std::make_tuple(longitude, latitude);
}

void GPS::setCoordinates(double longitude, double latitude)
{
    this->longitude = longitude;
    this->latitude = latitude;
}

std::tuple<int, int> GPS::chooseRoute(double maxSpeed, Route *route)
{
    return route->calculateRoute(maxSpeed);
}