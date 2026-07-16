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
#include "Dashboard.hpp"
#include "PenguinState.hpp"

bool menuShown = false;

CAMDriver cameraDriver;

HTTPServer http{cameraDriver};

bool dashboardRunning = false;
LSM6DSM imu;

PenguinState currentState;
IMUDriver imuDriver;

void displayMenu() 
{
    Serial.println("\n--- PENGUIN ---");
    Serial.println("[SPACE] launch dashboard");
    Serial.println(" [t] : launch test bench");
    Serial.println(" [s] : scan I2C bus");
    Serial.println("------------------------");
}


void runTaskSpace() 
{
    Serial.println("\n>> ---launching dashboard");
    run_dashboard();
}

void runTaskT() 
{
    Serial.println("\n>> ---launching test bench");
    run_test_bench();
}

void runTaskS() 
{
    recoverI2C();
    delay(50);

    Serial.println("\n>> ---scanning I2C bus");
    scanI2C();
    delay(1000);
}

void setup()
{
    Serial.begin(921600);

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

    imu.init(); 
    Serial.println("IMU --calibrating | hold still"); 
    delay(100);
    imu.calibrateGyro(200); 
    Serial.println("IMU --calibrated"); 

    led_startup();
    displayMenu();
}

void loop()
{
    currentState.imu = imuDriver.read();

    if (dashboardRunning) {
        http.update(currentState);
    }

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

            case ' ':
                runTaskSpace(); 
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
