#pragma once
#include <string>
#include "Client.h"
#include "Invoice.h"
class Billing
{
private:
    std::string billingId;

public:
    Billing(std::string billingId);
    std::string getBillingId();
    void processInvoice(Invoice *invoice, Client *client);
};