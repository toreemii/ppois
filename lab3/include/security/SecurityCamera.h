#pragma once
#include <string>

class SecurityCamera {
public:
    SecurityCamera(int cameraId, const std::string& location);
    void startRecording();
    void stopRecording();

private:
    int cameraIdentification;
    std::string cameraLocation;
    bool isRecording;
};