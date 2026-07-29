
/**
 * @file        dashboard.cpp
 * @brief       Connects to Wi-Fi and starts the local async web server and WebSocket endpoints
 * @author      Jeevan Sanchez
 * @date        2026-07-15
 *
 * PENGUIN
 */

#pragma onces

#include <Arduino.h>
#include <WiFi.h>
#include "web_socket_server.hpp"
#include "http_server.hpp"

void run_dashboard();
