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

Adafruit_LSM6DSL imu;

void test_imu() 
{
    Serial.println("PENGUIN ---IMU testing");

    if (!imu.begin_I2C(0x6A, &Wire)) 
    {
        Serial.println("failed to init LSM6DSM chip");
        return;
    }

    Serial.println("connected  ---streaming data... Press any key to stop.");

    while (!Serial.available()) 
    {
        sensors_event_t accel;
        sensors_event_t gyro;
        sensors_event_t temp;
        imu.getEvent(&accel, &gyro, &temp);

        Serial.printf("Accel X: %.2f, Y: %.2f, Z: %.2f | Gyro X: %.2f, Y: %.2f, Z: %.2f\n", 
                      accel.acceleration.x, accel.acceleration.y, accel.acceleration.z,
                      gyro.gyro.x, gyro.gyro.y, gyro.gyro.z);
                      
        delay(350);
    }

    while (Serial.available()) {
        Serial.read();
    }

    Serial.println("[SUCCESS] IMU data tracking loop complete.");
}
