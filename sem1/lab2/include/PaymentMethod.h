#pragma once
#include <iostream>

class PaymentMethod
{
public:
    virtual void processPayment() = 0;
};

class CardPayment : public PaymentMethod
{
public:
    void processPayment() override
    {
        std::cout << "Оплачено картой" << std::endl;
    }
};

class CashPayment : public PaymentMethod
{
public:
    void processPayment() override
    {
        std::cout << "Оплачено наличными" << std::endl;
    }
};

class CheckPayment : public PaymentMethod
{
public:
    void processPayment() override
    {
        std::cout << "Оплачено чеком" << std::endl;
    }
};