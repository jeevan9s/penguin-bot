/**
 * @file        test_leds.cpp
 * @brief       LED sequence testing.
 * @author      Jeevan Sanchez
 * @date        2026-06-29
 *
 * PENGUIN
 */

#include "test_leds.hpp"
extern Adafruit_MCP23X17 mcp;

void test_leds(void) {
    Serial.begin(38400); 
    Serial.println("PENGUIN ---LED testing");



    for (int i = 0; i < 3; i++) {
        mcp.pinMode(ledPins[i], OUTPUT); 
    }

    Serial.println("LEDs initialized.");
    delay(100);

    for (int i = 0; i < 3; i++) {
        mcp.digitalWrite(ledPins[i], HIGH);
        Serial.printf("flashing LED on MCP pin %d\n", ledPins[i]);


        delay(800);
        mcp.digitalWrite(ledPins[i], LOW);
    }

}
