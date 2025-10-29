#include "DigitalDevice.h"

DigitalDevice::DigitalDevice(int deviceId)
    : deviceIdentification(deviceId), isConnected(false), currentUser("") {}

void DigitalDevice::connect() {
    isConnected = true;
}

void DigitalDevice::disconnect() {
    isConnected = false;
    currentUser = "";
}