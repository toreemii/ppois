#pragma once
#include <iostream>
#include <string>

class Product
{
private:
    std::string name;
    double price;
    int amount;

public:
    Product(const std::string &name, double price, int amount) : name(name), price(price), amount(amount) {}

    bool operator<(const Product &other) const
    {
        return price < other.price;
    }

    std::string getName() const
    {
        return name;
    }
    double getPrice() const
    {
        return price;
    }
    int getAmount() const
    {
        return amount;
    }

    friend std::ostream &operator<<(std::ostream &os, const Product &product)
    {
        os << product.name << "($" << product.price << ", " << product.amount << ")";
        return os;
    }
};