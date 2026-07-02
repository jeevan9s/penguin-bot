/**
 * @file        main.cpp
 * @brief       Main entry point
 * @author      Jeevan Sanchez
 * @date        2026-06-29
 *
 * PENGUIN
 */

#include "config.hpp"
#include "test_bench.hpp"

bool menuShown = false;

void displayMenu() 
{
    Serial.println("\n--- PENGUIN ---");
    Serial.println(" [t] : launch test bench");
    Serial.println(" [s] : scan I2C bus");
    Serial.println("------------------------");
}

void runTaskT() 
{
    Serial.println("\n>> ---launching test bench");
    run_test_bench();
}

void runTaskS() 
{
    enable_cam();
    startCameraClock();
    delay(50);

    Serial.println("\n>> ---scanning I2C bus");
    scanI2C();
    delay(1000);
}


void setup()
{
    Serial.begin(38400);

    pinMode(Pins::MCU::MCP_RESET, OUTPUT);
    digitalWrite(Pins::MCU::MCP_RESET, HIGH);

    delay(50);

    while (!Serial && millis() < 4000) {
        delay(10);
    }

    Serial.println("\n==============================");
    Serial.println("PENGUIN ---initializing");

    if (init_mcp())
    {
        Serial.println("PENGUIN ---initialized");
    }
    else
    {
        Serial.println("MCP init failure");
    }

    mcp.pinMode(Pins::MCP::CAM_LED, OUTPUT);
    mcp.pinMode(Pins::MCP::DBG_LED, OUTPUT);
    mcp.pinMode(Pins::MCP::WIFI_LED, OUTPUT);

    mcp.pinMode(Pins::MCP::VMOT_EN, OUTPUT);

    led_startup();
    displayMenu();
}

void loop()
{
    if (!menuShown && millis() > 5000) 
    {
        displayMenu();
        menuShown = true;
    }

    if (Serial.available() > 0) 
    {
        char choice = Serial.read();
        menuShown = true; 

        switch (choice) 
        {
            case 't':
            case 'T':
                runTaskT();
                displayMenu(); 
                break;

            case 's':
            case 'S':
                runTaskS();
                displayMenu(); 
                break;
                
            case 'm':
            case 'M':
                displayMenu();
                break;

            case '\n':
            case '\r':
                break;

            default:
                Serial.print("'");
                Serial.print(choice);
                Serial.println("' is invalid. Press 'm' for menu.");
                break;
        }
    }
}
