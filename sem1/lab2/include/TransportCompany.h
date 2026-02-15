#pragma once
#include <vector>
#include <string>
#include "Depot.h"
#include "IClient.h"
#include "IOrder.h"
#include "Analytics.h"
#include "Logistics.h"

class TransportCompany
{
private:
    std::vector<Depot> depots;
    std::vector<IClient *> clients;
    std::vector<IOrder *> orders;
    Analytics analytics;
    Logistics logistics;
    std::string companyName;
    std::tm lastAuditDate;

public:
    TransportCompany(std::vector<Depot> depots, std::vector<IClient *> clients, std::vector<IOrder *> orders,
                     Analytics analytics, Logistics logistics);
    void addClient(IClient *client);
    void addOrder(IOrder *order);
    void addDepot(Depot depot);
    std::vector<IClient *> getClients();
    std::vector<IOrder *> getOrders();
    TransportCompany(const std::string &name);
    std::string getCompanyName();
    std::tm &getLastAuditDate();
    void setLastAuditDate(const std::tm &date);
};