
/**
 * @file        config.cpp
 * @brief       System configuration and utility.
 * @author      Jeevan Sanchez
 * @date        2026-06-29
 *
 * PENGUIN
 */

#include "config.hpp"

const char* ssid = "Health2024";
const char* pswd = "Rexdale2024";

Adafruit_MCP23X17 mcp;

int blinksRemaining = 0;
unsigned long lastBlink = 0;
uint8_t activeBlinkPin = 0;
int blinkCount = 0;

bool init_mcp(void) {
    Wire.begin(Pins::MCU::SDA, Pins::MCU::SCL, 100000);
    
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

void recoverI2C() {
    Wire.end(); 
    delay(10);

    pinMode(Pins::MCU::SDA, INPUT_PULLUP);
    pinMode(Pins::MCU::SCL, INPUT_PULLUP);
    delay(10);

    if (digitalRead(Pins::MCU::SDA) == LOW) {
        pinMode(Pins::MCU::SCL, OUTPUT);

        for (int i = 0; i < 16; i++) {
            digitalWrite(Pins::MCU::SCL, LOW);
            delayMicroseconds(10);
            digitalWrite(Pins::MCU::SCL, HIGH);
            delayMicroseconds(10);
        }
    }

    pinMode(Pins::MCU::SDA, OUTPUT);
    digitalWrite(Pins::MCU::SDA, LOW);
    delayMicroseconds(10);
    digitalWrite(Pins::MCU::SCL, HIGH); 
    delayMicroseconds(10);
    digitalWrite(Pins::MCU::SDA, HIGH);
    delayMicroseconds(10);

    Wire.begin(Pins::MCU::SDA, Pins::MCU::SCL); 
}


// non-blocking led stuff
void blinkP(uint8_t pin, int count) {
    if (blinksRemaining == 0) blinksRemaining = count * 2;

    if (millis() - lastBlink > 200) {
        lastBlink = millis();
        bool current = mcp.digitalRead(pin);
        mcp.digitalWrite(pin, !current);
        blinksRemaining--;

        if (blinksRemaining == 0) mcp.digitalWrite(pin, LOW);
    }
}

float lerp(float current, float target, float rate, float dt) {
    // move current to target smoothly based on rate
    return current + (target - current) * (1.0f - expf(-rate * dt));
}