#pragma once
#include <string>
#include "Order.h"
#include "Client.h"
#include "Notification.h"
#include "PaymentMethod.h"

class Invoice
{
private:
    std::string invoiceId;
    double amount;
    bool isPaid;
    Notification *notification;
    Order *relatedOrder;

public:
    Invoice(std::string invoiceId, double amount, bool isPaid, Notification *notification, Order *relatedOrder);
    void generateInvoice(Order *order);
    void sentToClient(Client *client);
    bool checkPayment(PaymentMethod *payment);
    std::string getInvoiceId();
    double getAmount();
    bool getIsPaid();
    Order *getRelatedOrder();
};