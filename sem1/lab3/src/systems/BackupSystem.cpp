#include "BackupSystem.h"
#include <iostream>

void BackupSystem::createBackup() {
    lastBackupTime = "сегодня";
    std::cout << "Резервная копия создана" << std::endl;
}

void BackupSystem::restoreFromBackup(const std::string& backupTime) {
    if (!backupTime.empty()) {
        std::cout << "Восстановлено из " << backupTime << std::endl;
    }
}