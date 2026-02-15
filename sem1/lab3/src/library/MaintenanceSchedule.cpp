#include "MaintenanceSchedule.h"

void MaintenanceSchedule::addTask(const std::string& task) {
    if (!task.empty()) {
        taskList.push_back(task);
    }
}

void MaintenanceSchedule::completeTask(const std::string& task) {
    for (size_t index = 0; index < taskList.size(); ++index) {
        if (taskList[index] == task) {
            taskList.erase(taskList.begin() + index);
            return;
        }
    }
}