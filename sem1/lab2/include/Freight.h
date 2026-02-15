#pragma once
#include <string>
#include <iostream>
#include "Exceptions.h"

class Freight
{

private:
    std::string freightId;
    double weight;
    std::string type;
    double length;
    double width;
    double height;
    std::string material;
    std::string category;
    double value;
    bool isInsured;

public:
    Freight() {}
    Freight(std::string freightId, double weight, bool isInsured);
    bool isHazardous();
    std::string getFreightId();
    double getWeight();
    double getValue();
    std::string getType();
    void packFreight();
    double calculateVolume() const;
    bool checkIfFragile() const;
    void updateValue(double newValue);
    void setWeight(double newWeight);
    void setLength(double length);
    void setWidth(double width);
    void setHeight(double height);
    void setCategory(std::string categoty);
};