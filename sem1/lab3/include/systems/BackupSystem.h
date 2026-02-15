#pragma once
#include <string>

class BackupSystem {
public:
    void createBackup();
    void restoreFromBackup(const std::string& backupTime);

private:
    std::string lastBackupTime;
    std::string storagePath;
};