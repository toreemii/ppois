#include "../include/AuditManager.h"
#include <iostream>
#include <ctime>

void AuditManager::auditOperations(TransportCompany *company)
{
    std::cout << "Аудиторские операции для " << company->getCompanyName() << " в " << std::asctime(&company->getLastAuditDate()) << std::endl;
}
