/**
 * @file        test_wifi.cpp
 * @brief       WiFi testing.
 * @author      Jeevan Sanchez
 * @date        2026-06-29
 *
 * PENGUIN
 */

#include "test_wifi.hpp"
extern Adafruit_MCP23X17 mcp;

void test_wifi(const char* ssid, const char* pswd) {
    Serial.printf("\nconnecting to: %s\n", ssid);
    
    WiFi.disconnect(true);
    delay(100);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pswd);

    int timeout_idx = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        mcp.digitalWrite(Pins::MCP::WIFI_LED, HIGH); 
        delay(200); 
        mcp.digitalWrite(Pins::MCP::WIFI_LED, LOW); 
        delay(200); 

        Serial.print(".");
        timeout_idx++;
        if (timeout_idx >= 28)
            break;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.printf("\nconnected to: %s\n", ssid);
        mcp.digitalWrite(Pins::MCP::WIFI_LED, HIGH);
    }
    else
    {
        Serial.printf("\nFailed to connect. Status: %d\n", WiFi.status());
    }
}

