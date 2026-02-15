#pragma once
#include <vector>
#include <string>

class MaintenanceSchedule {
public:
    void addTask(const std::string& task);
    void completeTask(const std::string& task);

private:
    std::vector<std::string> taskList;
};