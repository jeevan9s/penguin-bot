/**
 * @file        CamStream.hpp
 * @brief       Capture and stream camera frames over HTTP using a chunked
 *              multipart/x-mixed-replace response (server-driven, no
 *              dedicated FreeRTOS task, no cross-task buffer writes).
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

    struct StreamState {
        CAMDriver* camera;
        camera_fb_t* frame = nullptr;   // currently held frame buffer, or null
        size_t frameOffset = 0;         // bytes of frame->buf already sent
        String header;                 // pending boundary+headers not yet sent
        size_t headerOffset = 0;        // bytes of header already sent
        bool needNewFrame = true;       // true when should capture next

        explicit StreamState(CAMDriver* cam) : camera(cam) {}
    };

    static size_t fillChunk(StreamState* state, uint8_t* buffer, size_t maxLen, size_t index);
};