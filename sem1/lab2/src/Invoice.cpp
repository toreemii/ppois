#include "../include/Invoice.h"

Invoice::Invoice(std::string invoiceId, double amount, bool isPaid, Notification *notification, Order *relatedOrder)
    : invoiceId(invoiceId), amount(amount), isPaid(isPaid), notification(notification), relatedOrder(relatedOrder) {}

std::string Invoice::getInvoiceId()
{
    return invoiceId;
}
double Invoice::getAmount()
{
    return amount;
}
bool Invoice::getIsPaid()
{
    return isPaid;
}

void Invoice::generateInvoice(Order* order) {
    
}
void Invoice::sentToClient(Client *client)
{
    notification->sendNotification(client, "Счет " + invoiceId + " для " + std::to_string(amount));
}
bool Invoice::checkPayment(PaymentMethod *payment)
{
    isPaid = true;
    std::cout << "Оплата подтверждена по счету" << invoiceId << std::endl;
    return isPaid;
}
Order *Invoice::getRelatedOrder()
{
    return relatedOrder;
}
