/**
 * @file        config.hpp
 * @brief       System configuration.
 * @author      Jeevan Sanchez
 * @date        2026-06-28
 *
 * PENGUIN
 */

#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>

#include <Adafruit_MCP23X17.h>
#include <LSM6DSM.h>

extern LSM6DSM imu;

#include "pinouts.hpp"

extern Adafruit_MCP23X17 mcp;

bool init_mcp(void);
void led_startup(void);
void blinkLED(uint8_t ledPin, int count, int delayMs=200);
void scanI2C();
void recoverI2C();
void blinkP(uint8_t pin, int count);


// WIFI creds
extern const char* ssid;
extern const char* pswd;

// LED state
extern int blinksRemaining;
extern unsigned long lastBlink;
extern uint8_t activeBlinkPin;
extern int blinkCount; 
