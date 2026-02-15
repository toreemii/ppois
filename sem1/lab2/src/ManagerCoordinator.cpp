#include "../include/ManagerCoordinator.h"
#include <iostream>

void ManagerCoordinator::addManager(Manager *manager)
{
    std::cout << "Менеджер" << manager->getManagerId() << "добавлен в логистику\n";
}