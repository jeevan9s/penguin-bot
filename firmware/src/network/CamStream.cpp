/**
 * @file        CamStream.cpp
 * @brief       Capture and stream camera frames over HTTP.
 * @author      Jeevan Sanchez
 * @date        2026-07-15
 *
 * PENGUIN
 */

#include <Arduino.h>
#include "CamStream.hpp"
#undef HTTP_GET

CameraStream::CameraStream(AsyncWebServer& server, CAMDriver& camera) : camera_(camera) 
{
    server.on("/stream", WebRequestMethod::HTTP_GET, [this](AsyncWebServerRequest *request) {
        TaskParams* params = new TaskParams{request, &this->camera_};
        
        xTaskCreate(streamTask, "StreamTask", 8192, params, 1, NULL);
    });
}

void CameraStream::streamTask(void *pvParameters) {
    TaskParams* p = (TaskParams*)pvParameters;
    AsyncWebServerRequest* request = p->request;
    CAMDriver* cam = p->camera;

    AsyncResponseStream *response = request->beginResponseStream("multipart/x-mixed-replace;boundary=frame");
    
    while (request->client() && request->client()->connected()) {
        camera_fb_t *fb = cam->capture();
        if (fb) {
            response->printf("\r\n--frame\r\nContent-Type: image/jpeg\r\nContent-Length: %zu\r\n\r\n", fb->len);
            response->write(fb->buf, fb->len);
            cam->release(fb);
        }
        vTaskDelay(pdMS_TO_TICKS(30)); 
    }

    delete p; 
    vTaskDelete(NULL);
}