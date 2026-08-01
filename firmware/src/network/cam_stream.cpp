/**
 * @file        cam_stream.cpp
 * @brief       Capture and stream camera frames over HTTP.
 * @author      Jeevan Sanchez
 * @date        2026-07-15
 *
 * PENGUIN
 */

#include <Arduino.h>
#include "cam_stream.hpp"
#undef HTTP_GET

CameraStream::CameraStream(AsyncWebServer& server, CAMDriver& camera) : camera_(camera)
{
    server.on("/stream", WebRequestMethod::HTTP_GET, [this](AsyncWebServerRequest *request) {

        StreamState* state = new StreamState{&this->camera_};

        AsyncWebServerResponse *response = request->beginChunkedResponse(
            "multipart/x-mixed-replace;boundary=frame",
            [state](uint8_t *buffer, size_t maxLen, size_t index) -> size_t {
                return CameraStream::fillChunk(state, buffer, maxLen, index);
            });


        request->onDisconnect([state]() {
            if (state->frame) {
                state->camera->release(state->frame);
            }
            delete state;
        });

        request->send(response);
    });
}

size_t CameraStream::fillChunk(StreamState* state, uint8_t* buffer, size_t maxLen, size_t index)
{
    size_t written = 0;


    while (written < maxLen) {

        if (state->needNewFrame) {
            camera_fb_t* fb = state->camera->capture();
            if (!fb) {

                break;
            }
            state->frame = fb;
            state->frameOffset = 0;
            state->needNewFrame = false;

            char hdr[64];
            int hdrLen = snprintf(hdr, sizeof(hdr),
                "\r\n--frame\r\nContent-Type: image/jpeg\r\nContent-Length: %zu\r\n\r\n",
                fb->len);
            state->header = String(hdr, hdrLen);
            state->headerOffset = 0;
        }

        if (state->headerOffset < state->header.length()) {
            size_t remain = state->header.length() - state->headerOffset;
            size_t chunk = min(remain, maxLen - written);
            memcpy(buffer + written,
                   state->header.c_str() + state->headerOffset,
                   chunk);
            state->headerOffset += chunk;
            written += chunk;

            if (written >= maxLen) break; // buffer full, resume next call
        }

        if (state->frame && state->frameOffset < state->frame->len) {
            size_t remain = state->frame->len - state->frameOffset;
            size_t chunk = min(remain, maxLen - written);
            memcpy(buffer + written,
                   state->frame->buf + state->frameOffset,
                   chunk);
            state->frameOffset += chunk;
            written += chunk;
        }

        if (state->frame && state->frameOffset >= state->frame->len) {
            state->camera->release(state->frame);
            state->frame = nullptr;
            state->needNewFrame = true;

            vTaskDelay(pdMS_TO_TICKS(30));
        }
    }

    return written;
}