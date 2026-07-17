/**
 * @file        motor_driver.hpp
 * @brief       Class definition for DRV8833-controlled N20 MicroGear Motor driver. 
 * @author      Jeevan Sanchez
 * @date        2026-07-17
 * 
 *
 * PENGUIN
 */

#pragma once 

#include <Arduino.h>
#include "PenguinData.hpp"

extern Adafruit_MCP23X17 mcp;

class MotorDriver {
    public:
        MotorDriver(uint8_t motorIn1, uint8_t motorIn2, uint8_t encIn1, uint8_t encIn2); 
        bool begin(); 

        MotorData read(); 

        void setPWM(float pwm); 
        void stop(); 

    private:

};
