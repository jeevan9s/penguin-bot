/**
 * @file        test_imu.cpp
 * @brief       IMU testing. 
 * @author      Jeevan Sanchez
 * @date        2026-06-29
 *
 * PENGUIN
 */

#include <Arduino.h>
#include <Wire.h>
#include "config.hpp"
#include "test_imu.hpp"

void test_imu() {
    Serial.println("PENGUIN --- IMU testing");

    if (!imu.init(0x6A, Wire)) {
        Serial.println("failed to init LSM6DSM chip");
        return;
    }

    Serial.println("connected --- streaming data... press any key to stop.");

    while (!Serial.available()) {
        if (imu.dataReady()) {
            
            imu.readAll();

            Serial.printf("Accel X: %.2f, Y: %.2f, Z: %.2f | Gyro X: %.2f, Y: %.2f, Z: %.2f | Temp: %.2f\n", 
                          imu.accX(), imu.accY(), imu.accZ(),
                          imu.gyX(), imu.gyY(), imu.gyZ(), imu.readTemp());
        }
        
        delay(350);
    }

    while (Serial.available()) {
        Serial.read();
    }

    Serial.println("[SUCCESS] IMU data tracking loop complete.");
}
