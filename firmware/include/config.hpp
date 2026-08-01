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

/// @brief initializes the onboard MCP23017 IO expander
/// @return true on successful init
bool init_mcp();

/// @brief led flashing routine on system start
void led_startup();

/// @brief simple LED blink (blocking)
/// @param ledPin LED IO pin
/// @param count how many blinks
/// @param delayMs interval between blinks
void blinkLED(uint8_t ledPin, int count, int delayMs=200);

/// @brief scan the I2C bus for devices 
void scanI2C();

/// @brief resets and clears a stuck I2C bus
void recoverI2C();

/// @brief non-blocking LED blink
/// @param pin the LED pin
/// @param count the amount of blinks 
void blinkP(uint8_t pin, int count);

/// @brief linearly interpolates between two values in a frame-rate independent manner
/// @param current the starting value
/// @param target the destination value
/// @param rate the tracking speed (higher values mean faster interpolation)
/// @param dt the delta time since the last frame in seconds
/// @return the smoothly interpolated float value
float lerp(float current, float target, float rate, float dt); 

// WIFI creds
extern const char* ssid;
extern const char* pswd;

// LED state
extern int blinksRemaining;
extern unsigned long lastBlink;
extern uint8_t activeBlinkPin;
extern int blinkCount; 

