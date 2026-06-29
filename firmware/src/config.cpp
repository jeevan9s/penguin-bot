
/**
 * @file        config.cpp
 * @brief       System configuration.
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