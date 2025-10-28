#include "../include/Freight.h"

Freight::Freight(std::string freightId, double weight, bool isInsured)
    : freightId(freightId), weight(weight), isInsured(isInsured) {}

void Freight::setLength(double length)
{
    this->length = length;
}
void Freight::setWidth(double width)
{
    this->width = width;
}
void Freight::setHeight(double height)
{
    this->height = height;
}

void Freight::setCategory(std::string category) {
    this->category = category;
}

std::string Freight::getFreightId()
{
    return freightId;
}
double Freight::getWeight()
{
    return weight;
}
std::string Freight::getType()
{
    return type;
}

double Freight::getValue()
{
    return value;
}

bool Freight::isHazardous()
{
    return type == "Опасный";
}

void Freight::packFreight()
{
    std::cout << "Груз " << freightId << " упакован" << std::endl;
}
void Freight::setWeight(double newWeight)
{
    if (newWeight < 0)
    {
        throw InvalidWeightException();
    }
    weight = newWeight;
}

double Freight::calculateVolume() const
{
    if (length < 0 || width < 0 || height < 0)
    {
        throw FreightDimensionException();
    }
    return length * width * height;
}

bool Freight::checkIfFragile() const
{
    return category == "fragile";
}

void Freight::updateValue(double newValue)
{
    if (newValue >= 0)
    {
        value = newValue;
    }
}