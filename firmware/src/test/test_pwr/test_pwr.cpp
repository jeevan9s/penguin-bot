/**
 * @file        test_imu.cpp
 * @brief       Power testing (enables, sensing). 
 * @author      Jeevan Sanchez
 * @date        2026-06-30
 *
 * PENGUIN
 */

#include <Arduino.h>
#include "config.hpp"
#include "test_pwr.hpp"

// ENABLE: VMOT, CAM_PWR
// SENSE: VBATT

void test_pwr(void) {
    for (int i = 1; i <= 3; i++) {
        switch(i) {
            case 1:
                // VBATT SENSE
                Serial.println("testing VBATT SENSE...");
                int raw = analogRead(Pins::MCU::VBATT_SENSE);
                float voltage = (raw / 4095.0) * 3.3 * ((100.0 + 47.0) / 47.0);
                Serial.printf("VBATT sense: %.2fV\n", voltage);
                blinkDebug(1);
                break;

            case 2:
                // VMOT EN
                Serial.println("enabling VMOT [7.4V]"); 
                mcp.digitalWrite(Pins::MCP::VMOT_EN, HIGH);    
                blinkDebug(2);
                delay(5000);
                mcp.digitalWrite(Pins::MCP::VMOT_EN, LOW); 
                break;
            
            case 3:
                // CAM AVDD DVDD EN
                Serial.println("enabling CAM power [AVDD = 2.8V, DVDD = 1.2V]");
                mcp.digitalWrite(Pins::MCP::CAM_PWR_EN, HIGH);    
                blinkDebug(3);
                delay(5000);
                mcp.digitalWrite(Pins::MCP::CAM_PWR_EN, LOW);
                break;
            
            default:
                break;
        }
        delay(500); 
    }
}