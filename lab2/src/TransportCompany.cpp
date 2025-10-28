#include "../include/TransportCompany.h"
#include "../include/Logistics.h"

TransportCompany::TransportCompany(std::vector<Depot> depots, std::vector<IClient *> clients,
                                   std::vector<IOrder *> orders, Analytics analytics, Logistics logistics)
    : depots(depots), clients(clients), orders(orders), analytics(analytics), logistics(logistics) {}

void TransportCompany::addClient(IClient *client)
{
    if (client == nullptr)
    {
        throw InvalidArgumentException();
    }
    clients.push_back(client);
}

void TransportCompany::addOrder(IOrder *order)
{
    if (order == nullptr)
    {
        throw InvalidArgumentException();
    }
    orders.push_back(order);
    logistics.addOrder(order);
}

void TransportCompany::addDepot(Depot depot)
{
    depots.push_back(depot);
}

std::vector<IClient *> TransportCompany::getClients()
{
    return clients;
}

std::vector<IOrder *> TransportCompany::getOrders()
{
    return logistics.getOrders();
}

std::string TransportCompany::getCompanyName()
{
    return companyName;
}
std::tm &TransportCompany::getLastAuditDate()
{
    return lastAuditDate;
}
void TransportCompany::setLastAuditDate(const std::tm &date)
{
    lastAuditDate = date;
}

TransportCompany::TransportCompany(const std::string &name)
    : companyName(name)
{
    std::time_t t = std::time(nullptr);
    lastAuditDate = *std::localtime(&t);
}