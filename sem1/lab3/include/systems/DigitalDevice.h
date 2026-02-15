#pragma once
#include <string>

class DigitalDevice {
public:
    DigitalDevice(int deviceId);
    void connect();
    void disconnect();

private:
    int deviceIdentification;
    bool isConnected;
    std::string currentUser;
};