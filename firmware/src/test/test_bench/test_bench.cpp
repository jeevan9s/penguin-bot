/**
 * @file        test_bench.cpp
 * @brief       Test bench implementation.
 * @author      Jeevan Sanchez
 * @date        2026-06-29
 *
 * PENGUIN
 */

#include <Arduino.h>
#include "config.hpp"
#include "test_bench.hpp"

void run_test_bench()
{
    while (true)
    {
        Serial.println("\n=== TEST BENCH ===");
        Serial.println("1 : LEDs");
        Serial.println("2 : WIFI");
        Serial.println("3 : IMU");
        Serial.println("4 : POWER");
        Serial.println("5 : CAMERA");
        Serial.println("6 : MOTORS");
        Serial.println("x : Exit");

        while (!Serial.available())
        {
            delay(10);
        }

        char choice = Serial.read();
        while (Serial.available() > 0)
        {
            Serial.read();
        }

        switch (choice)
        {
        case '1':
            test_leds();
            break;

        case '2':
            test_wifi(ssid, pswd);
            break;

        case '3':
            test_imu();
            break;

        case '4':
            test_pwr();
            break;

        case '5':
            recoverI2C();
            setup_cam();
            delay(1000);

            // test_cam_serial();
            setup_wifi();
            test_cam_wifi();
            break;

        case '6':
            test_motors();
            break;

        case 'x':
        case 'X':
            return;
        }
    }
}
