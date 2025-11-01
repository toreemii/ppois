#include "../include/Client.h"

Client::Client(std::string clientId, std::string name, std::string address,
               PaymentManager *pm, ClientActivityLogger *al, LoyaltyManager *lm)
    : clientId(clientId), name(name), address(address), paymentManager(pm), activityLogger(al), loyaltyManager(lm){}

std::string Client::getClientId()
{
    return clientId;
}
std::string Client::getName()
{
    return name;
}
std::string Client::getAddress()
{
    return address;
}
std::string Client::getPhoneNumber()
{
    return phoneNumber;
}
std::string Client::getEmail()
{
    return email;
}
void Client::setEmail(std::string email)
{
    this->email = email;
}
void Client::setPhoneNumber(std::string phoneNumber)
{
    this->phoneNumber = phoneNumber;
}
void Client::updateContactInfo(std::string newPhone, std::string newEmail)
{
    phoneNumber = newPhone;
    email = newEmail;
}
std::vector<IOrder*> Client::getOrders()
{
    return orders;
}
void Client::placeOrder(IOrder *order)
{
    orders.push_back(order);
}
double Client::getDiscountRate() const
{
    return discountRate;
}
void Client::setDiscountRate(double rate)
{
    discountRate = rate;
}
int Client::getLoyaltyPoints() const
{
    return loyaltyPoints;
}
std::tm Client::getLastOrderDate() const
{
    return lastOrderDate;
}

void Client::makePayment(int choice)
{
    paymentManager->makePayment(choice);
}

void Client::makeOrder(std::string orderId, std::vector<Passenger> passengersList, PaymentMethod *paymentType,
                       double weightOfOrder, Vehicle *vehicle)
{
    paymentManager->makeOrderPayment(this, orderId, passengersList, paymentType, weightOfOrder, vehicle);
}

void Client::logClientActivity()
{
    activityLogger->logClientActivity(this);
}

void Client::applyLoyaltyDiscount(double percentage)
{
    loyaltyManager->applyLoyaltyDiscount(this, percentage);
}

bool Client::checkEligibilityForPriority() 
{
    return loyaltyManager->checkEligibilityForPriority(this);
}