/**
 * @file        dashboard.cpp
 * @brief       Connects to Wi-Fi and starts the local async web server and WebSocket endpoints
 * @author      Jeevan Sanchez
 * @date        2026-07-15
 *
 * PENGUIN
 */

#include "dashboard.hpp"

extern HTTPServer http;
extern bool dashboardRunning;
void run_dashboard()
{
    WiFi.mode(WIFI_STA);
    Serial.println("WIFI --connecting...");
    
    WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info) {
        if (event == ARDUINO_EVENT_WIFI_STA_GOT_IP) {
            Serial.println("WIFI --connected");
            
            Serial.print("ESP32 IP Address: ");
            Serial.println(WiFi.localIP());
            
            http.begin();
            dashboardRunning = true;

            activeBlinkPin = Pins::MCP::WIFI_LED;
            blinkCount = 3;
            blinksRemaining = blinkCount * 2;
        } else if (event == ARDUINO_EVENT_WIFI_STA_DISCONNECTED) {
            Serial.println("WIFI --disconnected");
            dashboardRunning = false; 
            activeBlinkPin = Pins::MCP::DBG_LED;
            blinkCount = 3;
            blinksRemaining = blinkCount * 2;
        }
    });

    WiFi.begin(ssid, pswd);
}
