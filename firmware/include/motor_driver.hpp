/**
 * @file        motor_driver.hpp
 * @brief       Class definition for DRV8833-controlled N20 MicroGear Motor driver. 
 * @author      Jeevan Sanchez
 * @date        2026-07-17
 * 
 * Uses the ESP32Encoder wrapper for the ESP Pulse Count Peripheral (PCNT)
 *
 * PENGUIN
 */

#pragma once 

#include <Arduino.h>
#include "penguin_data.hpp"
#include <ESP32Encoder.h>
#include <Adafruit_MCP23X17.h>

extern Adafruit_MCP23X17 mcp;

class MotorDriver {
    public:
        MotorDriver(uint8_t motorIn1, uint8_t motorIn2, uint8_t encP1, uint8_t encP2); 
        void begin(); 

        MotorData read(); 

        void run(int pwm); 
        void stop(); 

    private:
        uint8_t _motorIn1; 
        uint8_t _motorIn2; 
        uint8_t _encP1; 
        uint8_t _encP2; 

        uint8_t _in1; 
        uint8_t _in2; 

        ESP32Encoder _encoder; 

        long _lastPosition; 
        unsigned long _lastTime; 
        float _currentRPM;
};
