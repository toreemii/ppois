#include "SecurityCamera.h"

SecurityCamera::SecurityCamera(int cameraId, const std::string& location)
    : cameraIdentification(cameraId), cameraLocation(location), isRecording(false) {}

void SecurityCamera::startRecording() {
    isRecording = true;
}

void SecurityCamera::stopRecording() {
    isRecording = false;
}