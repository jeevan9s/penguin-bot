/**
 * @file        test_motor.cpp
 * @brief       Header for testing N20 (with encoders) and Servo motors.
 * @author      Jeevan Sanchez
 * @date        2026-06-29
 *
 * PENGUIN
 */

// testing is just for one motor and servo -- not both
#include <Arduino.h>
#include "test_mtr.hpp"

Servo servoL;
Servo servoR;
volatile long encoderVal = 0;

extern Adafruit_MCP23X17 mcp;

void countPulse() {
    if (digitalRead(Pins::MCU::ENC_A_PH2) == HIGH) {
        encoderVal++;
    } else {
        encoderVal--;
    }
}

void printTicks(unsigned long durationMs) {
    unsigned long start = millis();
    while(millis() - start < durationMs) {
        Serial.print("encoder: ");
        Serial.println(encoderVal);
        delay(100);
    }
}

void motorSetup() {
    servoL.attach(Pins::MCU::L_SERVO); 
    servoR.attach(Pins::MCU::R_SERVO); 
    
    mcp.pinMode(Pins::MCP::VMOT_EN, OUTPUT); 
    mcp.digitalWrite(Pins::MCP::VMOT_EN, HIGH); 
    delay(500);

    pinMode(Pins::MCU::MOTA_IN1, OUTPUT); 
    pinMode(Pins::MCU::MOTA_IN2, OUTPUT); 
    pinMode(Pins::MCU::MOTB_IN1, OUTPUT); 
    pinMode(Pins::MCU::MOTB_IN2, OUTPUT); 

    pinMode(Pins::MCU::ENC_A_PH1, INPUT_PULLUP); 
    pinMode(Pins::MCU::ENC_A_PH2, INPUT_PULLUP); 

    attachInterrupt(digitalPinToInterrupt(Pins::MCU::ENC_A_PH1), countPulse, RISING);
}

void sweepServo()
{
    for (int i = 0; i <= 180; i++)
    {
        servoL.write(i);
        Serial.println("sweeping Servo to 180°"); 
        delay(15);
    }

    for (int i = 180; i >= 0; i--)
    {
        servoL.write(i);
        Serial.println("sweeping Servo back to 0"); 
        delay(15);
    }

    delay (500); 

        for (int i = 0; i <= 180; i++)
    {
        servoR.write(i);
        Serial.println("sweeping Servo to 180°"); 
        delay(15);
    }

    for (int i = 180; i >= 0; i--)
    {
        servoR.write(i);
        Serial.println("sweeping Servo back to 0"); 
        delay(15);
    }
}

void runDCMotors() {
    Serial.println("driving motor [FWD]");
    digitalWrite(Pins::MCU::MOTB_IN2, LOW);
    digitalWrite(Pins::MCU::MOTB_IN1, HIGH); 
    digitalWrite(Pins::MCU::MOTA_IN2, LOW);
    digitalWrite(Pins::MCU::MOTA_IN1, HIGH); 
    
    printTicks(2000);

    Serial.println("driving motor [OFF]");
    digitalWrite(Pins::MCU::MOTB_IN2, LOW);
    digitalWrite(Pins::MCU::MOTB_IN1, LOW);
    digitalWrite(Pins::MCU::MOTA_IN2, LOW);
    digitalWrite(Pins::MCU::MOTA_IN1, LOW);
    printTicks(1000);

    Serial.println("driving motor [REV]");
    digitalWrite(Pins::MCU::MOTB_IN1, LOW);
    digitalWrite(Pins::MCU::MOTB_IN2, HIGH);
    digitalWrite(Pins::MCU::MOTA_IN1, LOW);
    digitalWrite(Pins::MCU::MOTA_IN2, HIGH); 
    printTicks(2000);

    digitalWrite(Pins::MCU::MOTA_IN2, LOW);
}

void test_motors() {

   motorSetup();

    for (int i = 0; i < 2; i++) {
        switch(i) {
            case 0:
                Serial.println("testing SERVOS---");
                sweepServo(); 
                break;
            
            case 1: 
                Serial.println("testing N20 motors---");
                runDCMotors();
                break;

            default:
                break;
        }
    }
}
