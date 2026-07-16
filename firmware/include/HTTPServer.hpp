/**
 * @file        HTTPServer.hpp
 * @brief       Header for HTTP router.
 * @author      Jeevan Sanchez
 * @date        2026-07-15
 *
 * PENGUIN
 */

#pragma once

#include <ESPAsyncWebServer.h>
#include "WebSocketServer.hpp"
#include "PenguinState.hpp"

#include "CamStream.hpp" 

class HTTPServer {
public:
    HTTPServer(CAMDriver& cam); 
    void begin();
    void update(PenguinState &state);

private:
    AsyncWebServer server;
    WebSocketServer websocket;
    CAMDriver& camera_;
    CameraStream cameraStream; 

};