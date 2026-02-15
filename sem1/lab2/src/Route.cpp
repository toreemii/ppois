#include "../include/Route.h"

Route::Route(std::string routeId) : routeId(routeId) {}
RouteA::RouteA(std::string routeId) : Route(routeId) {}
RouteB::RouteB(std::string routeId) : Route(routeId) {}

std::tuple<int, int> RouteA::calculateRoute(double maxSpeed)
{
    if (maxSpeed <= 0)
        return std::make_tuple(0, 0);
    return std::make_tuple(static_cast<int>(38 * 100 / maxSpeed), 15);
}

std::tuple<int, int> RouteB::calculateRoute(double maxSpeed)
{
    if (maxSpeed <= 0)
        return std::make_tuple(0, 0);
    return std::make_tuple(static_cast<int>(3 * 100 / maxSpeed), 18);
}

std::string Route::getRouteId()
{
    return routeId;
}
