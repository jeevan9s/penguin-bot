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
        Serial.println("x : Exit");

        while (!Serial.available())
        {
            delay(10);
        }

        char choice = Serial.read();

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

            case 'x':
            case 'X':
                return;
        }
    }
}
