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
#include "dashboard.hpp"
#include "scheduler.hpp"
#include "penguin_state.hpp"
#include "behaviour.hpp"
#include "locomotion.hpp"
#include "servo_driver.hpp"
#include "balance_controller.hpp"
#include "velocity_controller.hpp"
#include "motion_config.hpp"
#include "tof_driver.hpp"
#include "oled_driver.hpp"

bool menuShown = false;
CAMDriver cameraDriver;
HTTPServer http{cameraDriver};
bool dashboardRunning = false;
LSM6DSM imu;

BalanceController balanceController(MotionConfig::BAL_KP, MotionConfig::BAL_KI, MotionConfig::BAL_KD, MotionConfig::TURBO_SPEED);
VelocityController leftVController(MotionConfig::VEL_KP, MotionConfig::VEL_KI, MotionConfig::VEL_KD, 255);
VelocityController rightVController(MotionConfig::VEL_KP, MotionConfig::VEL_KI, MotionConfig::VEL_KD, 255);
ServoDriver hipL(Pins::MCU::L_SERVO);
ServoDriver hipR(Pins::MCU::R_SERVO);
IMUDriver imuDriver;
BattDataDriver battDriver;
constexpr uint16_t TOF_CORRECTION_MM = 60;
TOFDriver sensor1(Pins::MCP::TOF_XSHUT_1, 0x31, 100.0, TOF_CORRECTION_MM);
TOFDriver sensor2(Pins::MCP::TOF_XSHUT_2, 0x32, 100.0, TOF_CORRECTION_MM);
TOFDriver sensor3(Pins::MCP::TOF_XSHUT_3, 0x33, 100.0, TOF_CORRECTION_MM);
MotorDriver motorL(Pins::MCU::MOTA_IN1, Pins::MCU::MOTA_IN2, Pins::MCU::ENC_A_PH1, Pins::MCU::ENC_A_PH2);
MotorDriver motorR(Pins::MCU::MOTB_IN1, Pins::MCU::MOTB_IN2, Pins::MCU::ENC_B_PH1, Pins::MCU::ENC_B_PH2);

Locomotion locomotion(balanceController, leftVController, rightVController, motorL, motorR, hipL, hipR);
Behaviour behaviour;

Scheduler scheduler(imuDriver, battDriver, sensor1, sensor2, sensor3, motorL, motorR);

namespace
{
bool initializeTofSensor(const char *label, TOFDriver &sensor)
{
    sensor.off();

    if (sensor.begin())
    {
        Serial.printf("%s --initialized\n", label);
        return true;
    }

    Serial.printf("%s init failure\n", label);
    return false;
}

void initializeAllTofSensors()
{
\    sensor1.off();
    sensor2.off();
    sensor3.off();
    delay(30);

    initializeTofSensor("TOF L", sensor1);
    initializeTofSensor("TOF M", sensor2);
    initializeTofSensor("TOF R", sensor3);
}

bool initializeIMU()
{
    if (!imuDriver.begin())
    {
        Serial.println("IMU init failure");
        return false;
    }

    Serial.println("IMU --calibrating | hold still");
    delay(100);
    imu.calibrateGyro(200);
    Serial.println("IMU --calibrated");
    return true;
}

void recoverSensors(bool force = false)
{
    static uint32_t lastHealthCheck = 0;
    uint32_t now = millis();

    if (!force && (now - lastHealthCheck < 1000))
    {
        return;
    }

    lastHealthCheck = now;

    if (force)
    {
        Serial.println("TOF --manual full recovery");
        recoverI2C();

        if (!probeI2C(0x20))
        {
            Serial.println("MCP --reinitializing");
            if (!init_mcp())
            {
                Serial.println("MCP reinit failure");
                return;
            }
        }

        initializeAllTofSensors();
        return;
    }

    if (force || !sensor1.ping())
    {
        Serial.println(force ? "TOF L --manual recover" : "TOF L --offline, reinitializing");
        initializeTofSensor("TOF L", sensor1);
    }

    if (force || !sensor2.ping())
    {
        Serial.println(force ? "TOF M --manual recover" : "TOF M --offline, reinitializing");
        initializeTofSensor("TOF M", sensor2);
    }

    if (force || !sensor3.ping())
    {
        Serial.println(force ? "TOF R --manual recover" : "TOF R --offline, reinitializing");
        initializeTofSensor("TOF R", sensor3);
    }
}
}

void displayMenu()
{
    Serial.println("\n--- PENGUIN ---");
    Serial.println(" [space] : launch dashboard");
    Serial.println(" [t] : launch test bench");
    Serial.println(" [s] : scan I2C bus");
    Serial.println(" [r] : recover sensors"); 
    Serial.println("------------------------");
}

void runDash()
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
    if (!probeI2C(0x20))
    {
        recoverI2C();
    }
    delay(50);

    Serial.println("\n>> ---scanning I2C bus");
    scanI2C();
    delay(1000);
}

void runTaskR() {
    Serial.println("\n>> --recovering sensors");
    recoverSensors(true);
}
void setup()
{
    Serial.begin(921600);

    pinMode(Pins::MCU::MCP_RESET, OUTPUT);
    digitalWrite(Pins::MCU::MCP_RESET, HIGH);

    delay(50);

    while (!Serial && millis() < 4000)
    {
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
    oledLoadingScreen(0);

    initializeAllTofSensors();

    if (cameraDriver.begin())
    {
        Serial.println("CAM --initialized");
    }
    else
    {
        Serial.println("CAM init failure");
    }
    oledLoadingScreen(25);

    mcp.pinMode(Pins::MCP::CAM_LED, OUTPUT);
    mcp.pinMode(Pins::MCP::DBG_LED, OUTPUT);
    mcp.pinMode(Pins::MCP::WIFI_LED, OUTPUT);
    oledLoadingScreen(50);

    initializeIMU();
    oledLoadingScreen(75);

    led_startup();
    oledLoadingScreen(85);
    displayMenu();

    motorL.begin();
    motorR.begin();
    oledLoadingScreen(90);
    hipL.begin(MotionConfig::DEFAULT_HIP_ANGLE, MotionConfig::MAX_HIP_ANGLE);
    hipR.begin(MotionConfig::DEFAULT_HIP_ANGLE, MotionConfig::MAX_HIP_ANGLE);
    oledLoadingScreen(95);

    behaviour.begin();
    oledLoadingScreen(100);
    delay(400);
}

void loop()
{
    if (blinksRemaining > 0)
    {
        blinkP(activeBlinkPin, blinkCount);
    }

    runDash();

    scheduler.update(penguin_state);
    recoverSensors();

    static uint32_t last = millis();
    uint32_t now = millis();

    float dt = (now - last) / 1000.0f;
    last = now;

    behaviour.update(penguin_commands, penguin_state, dt);
    locomotion.update(penguin_state, penguin_commands, dt);

    oled();

    if (dashboardRunning)
    {
        http.update(penguin_state);
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

        case ' ':
            runDash();
            break;

        case 'r':
        case 'R':
            runTaskR(); 
            break;

        case 'm':
        case 'M':
            displayMenu();
            break;

        case '\n':
        case '\r':
            break;

        default:

            break;
        }
    }
    delay(1);
}