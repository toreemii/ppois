#pragma once
#include <tuple>
#include <string>
class Route
{
private:
    std::string routeId;

public:
    Route(std::string routeId);
    virtual std::tuple<int, int> calculateRoute(double maxSpeed) = 0;
    std::string getRouteId();
};

class RouteA : public Route
{
public:
    RouteA(std::string routeId);
    std::tuple<int, int> calculateRoute(double maxSpeed) override;
};

class RouteB : public Route
{
public:
    RouteB(std::string routeId);
    std::tuple<int, int> calculateRoute(double maxSpeed) override;
};
