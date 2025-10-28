#pragma once
#include <vector>
#include "IClient.h"
#include "ClientActivityLogger.h"
#include "LoyaltyManager.h"
#include "PaymentManager.h"

class Order;
class ClientActivityLogger;
class LoyaltyManager;
class PaymentManager;

class Client
{
private:
    std::vector<IOrder*> orders;
    std::string clientId;
    std::string phoneNumber;
    std::string email;
    int loyaltyPoints;
    std::string preferredPaymentMethod;
    std::tm lastOrderDate;
    std::string clientType;
    double discountRate;
    std::string emergencyContact;
    std::string name;
    std::string address;
    PaymentManager *paymentManager;
    ClientActivityLogger *activityLogger;
    LoyaltyManager *loyaltyManager;

public:
    Client(std::string clientId, std::string name, std::string address,
           PaymentManager *pm, ClientActivityLogger *al, LoyaltyManager *lm);
    std::string getClientId();
    std::string getName();
    std::string getAddress();
    std::string getPhoneNumber();
    std::string getEmail();
    void setEmail(std::string email);
    void setPhoneNumber(std::string phoneNumber);
    void updateContactInfo(std::string newPhone, std::string newEmail);
    std::vector<IOrder*> getOrders();
    void placeOrder(IOrder *order);
    double getDiscountRate() const;
    void setDiscountRate(double rate);
    int getLoyaltyPoints() const;
    std::tm getLastOrderDate() const;
    void makePayment(int choice);
    void makeOrder(std::string orderId, std::vector<Passenger> passengersList, PaymentMethod *paymentType,
                   double weightOfOrder, Vehicle *vehicle);
    void logClientActivity();
    void applyLoyaltyDiscount(double percentage);
    bool checkEligibilityForPriority();
};