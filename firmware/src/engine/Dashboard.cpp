
/**
 * @file        Dashboard.cpp
 * @brief       Connects to Wi-Fi and starts the local async web server and WebSocket endpoints
 * @author      Jeevan Sanchez
 * @date        2026-07-15
 *
 * PENGUIN
 */

#include "Dashboard.hpp"

extern HTTPServer http;
extern bool dashboardRunning;

void run_dashboard()
{
    WiFi.begin(ssid, pswd);

    Serial.print("WIFI --connecting");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();

    Serial.print("IP: ");
    Serial.println(WiFi.localIP());


    http.begin();

    dashboardRunning = true;
}