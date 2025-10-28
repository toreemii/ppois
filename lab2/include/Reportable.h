#pragma once

class Reportable
{
public:
    virtual void submitTripReport(double distance, int hours, int minutes, int people, double cargo) = 0;
};