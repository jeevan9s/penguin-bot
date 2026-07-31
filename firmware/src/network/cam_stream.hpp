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

class CameraStream
{
public:
    /// @brief register "/stream" endpoint to establish chunked MJPEG video stream using multipart HTTP
    /// has allocation leak cleanup
    /// @param server reference to the async web stream server
    /// @param camera reference to the camera hardware driver
    CameraStream(AsyncWebServer &server, CAMDriver &camera);

private:
    CAMDriver &camera_;

    /// @brief interface representing stream data/state components
    struct StreamState
    {
        CAMDriver *camera;
        camera_fb_t *frame = nullptr; // currently held frame buffer, or null
        size_t frameOffset = 0;       // bytes of frame->buf already sent
        String header;                // pending boundary+headers not yet sent
        size_t headerOffset = 0;      // bytes of header already sent
        bool needNewFrame = true;     // true when should capture next

        explicit StreamState(CAMDriver *cam) : camera(cam) {}
    };

    /// @brief callback to populate the HTTP response buffer with MJPEG stream data chunks
    /// @param state pointer to persistent stream state
    /// @param buffer async web server destination bufffer
    /// @param maxLen maximum no. of bytes that can be written to the buffer in this invocation
    /// @param index total no. of bytes sent so far across all chunks for this request.
    /// @return the actual no. of bytes written to the buffer during this execution.
    static size_t fillChunk(StreamState *state, uint8_t *buffer, size_t maxLen, size_t index);
};