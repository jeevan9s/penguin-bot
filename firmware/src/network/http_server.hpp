/**
 * @file        http_server.hpp
 * @brief       Header for HTTP router.
 * @author      Jeevan Sanchez
 * @date        2026-07-15
 *
 * PENGUIN
 */

#pragma once

#include <ESPAsyncWebServer.h>
#include "web_socket_server.hpp"
#include "penguin_state.hpp"

#include "cam_stream.hpp"

/// @brief Async HTTP and WebSocket server manager for handling web routing, telemetry, and camera streaming
class HTTPServer
{
public:

    /// @brief construct with an instance of the camera driver
    HTTPServer(CAMDriver &cam);

    /// @brief initializes HTTP endpoint, starts websocket server, and listens for incoming traffic
    void begin();

    /// @brief update the websocket
    /// @param state global state instance
    void update(PenguinState &state);

private:
    AsyncWebServer server;
    WebSocketServer websocket;
    CAMDriver &camera_;
    CameraStream cameraStream;
};