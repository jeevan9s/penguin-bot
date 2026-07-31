/**
 * @file        web_socket_server.hpp
 * @brief       Header for WebSocketServer handling client connect, disconnect, telemetry
 * @author      Jeevan Sanchez
 * @date        2026-07-15
 *
 * PENGUIN
 */

#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "penguin_state.hpp"
#include "telemetry.hpp"
#include "config.hpp"

/// @brief server class for opening a Websocket server for telemetry (and possibly commands) over HTTP
/// wraps the ESP Asynchronous Web Server library
/// interfaces with the HTTPServer class on start 

class WebSocketServer {
    public:

        /// @brief registers the web-socket handler with the server
        /// @param server asynchronous web server
        WebSocketServer(AsyncWebServer &server); 

        /// @brief handle Websocket connection state and debug with non-blocking LED code
        void begin(); 

        /// @brief clears out disconnected clients, rate-limits, and sends serialized telemetry payload over Websocket
        /// @param state global state instance
        void update(const PenguinState &state); 

        /// @brief dashboard (client) connection status tracking
        bool clientConnected;

    private:
        /// @brief instansiate WS handler and set URI
        AsyncWebSocket ws{"/ws"}; 
        // static void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
        uint32_t lastTelemetryTime = 0; 
};

 