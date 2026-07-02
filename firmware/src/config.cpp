
/**
 * @file        config.cpp
 * @brief       System configuration and utility.
 * @author      Jeevan Sanchez
 * @date        2026-06-29
 *
 * PENGUIN
 */

#include "config.hpp"

const char* ssid = "JPhone";
const char* pswd = "jeevan1--";

Adafruit_MCP23X17 mcp;

bool init_mcp(void) {
    Wire.begin(Pins::MCU::SDA, Pins::MCU::SCL);
    
    if (!mcp.begin_I2C()) {
        return false; 
    }
    return true;
}

void led_startup(void) {
    mcp.digitalWrite(Pins::MCP::CAM_LED, HIGH);
    delay(400);
    mcp.digitalWrite(Pins::MCP::CAM_LED, LOW);
    delay(400); 

    mcp.digitalWrite(Pins::MCP::DBG_LED, HIGH);
    delay(300);
    mcp.digitalWrite(Pins::MCP::DBG_LED, LOW);
    delay(300); 

    mcp.digitalWrite(Pins::MCP::CAM_LED, HIGH);
    delay(200);
    mcp.digitalWrite(Pins::MCP::CAM_LED, LOW);
    delay(200);
    mcp.digitalWrite(Pins::MCP::DBG_LED, HIGH);
    delay(200); 

    mcp.digitalWrite(Pins::MCP::DBG_LED, LOW);
    mcp.digitalWrite(Pins::MCP::CAM_LED, HIGH);
    delay(200);
    mcp.digitalWrite(Pins::MCP::CAM_LED, LOW);
    delay(200); 
}

void blinkLED(uint8_t ledPin, int count, int delayMs) {
    for(int i = 0; i < count; i++) {
        mcp.digitalWrite(ledPin, HIGH);
        delay(delayMs);
        mcp.digitalWrite(ledPin, LOW);
        delay(delayMs);
    }
}

void scanI2C() {
    Serial.println("scanning I2C bus...");
    for(byte address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        if (Wire.endTransmission() == 0) {
            Serial.printf("Found device at 0x%02X\n", address);
        }
    }
}