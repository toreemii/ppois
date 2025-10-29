#include "AuditLog.h"

void AuditLog::logAction(const std::string& action) {
    if (!action.empty()) {
        logEntries.push_back(action);
    }
}

void AuditLog::clearLog() {
    logEntries.clear();
}