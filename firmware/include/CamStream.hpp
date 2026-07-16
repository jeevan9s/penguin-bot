/**
 * @file        CamStream.hpp
 * @brief       Capture and stream camera frames over HTTP.
 * @author      Jeevan Sanchez
 * @date        2026-07-15
 *
 * PENGUIN
 */
#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "cam_driver.hpp"

class CameraStream {
public:
    CameraStream(AsyncWebServer& server, CAMDriver& camera);
    
private:
    CAMDriver& camera_;
    static void streamTask(void *pvParameters);
    
    struct TaskParams {
        AsyncWebServerRequest* request;
        CAMDriver* camera;
    };
};