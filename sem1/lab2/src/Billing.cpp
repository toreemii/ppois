#include "../include/Billing.h"

Billing::Billing(std::string billingId) : billingId(billingId) {}

std::string Billing::getBillingId()
{
    return billingId;
}
void Billing::processInvoice(Invoice *invoice, Client *client)
{
    invoice->generateInvoice(invoice->getRelatedOrder());
    std::cout << "Счёт обработан для клиента " << client->getClientId() << ": " << billingId << std::endl;
}