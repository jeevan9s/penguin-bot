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
TOFDriver sensor1(Pins::MCP::TOF_XSHUT_1, 0x31);
TOFDriver sensor2(Pins::MCP::TOF_XSHUT_2, 0x32);
TOFDriver sensor3(Pins::MCP::TOF_XSHUT_3, 0x33);
MotorDriver motorL(Pins::MCU::MOTA_IN1, Pins::MCU::MOTA_IN2, Pins::MCU::ENC_A_PH1, Pins::MCU::ENC_A_PH2);
MotorDriver motorR(Pins::MCU::MOTB_IN1, Pins::MCU::MOTB_IN2, Pins::MCU::ENC_B_PH1, Pins::MCU::ENC_B_PH2);

Locomotion locomotion(balanceController, leftVController, rightVController, motorL, motorR, hipL, hipR);
Behaviour behaviour; 

Scheduler scheduler(imuDriver, battDriver, sensor1, sensor2, sensor3, motorL, motorR);

void displayMenu()
{
    Serial.println("\n--- PENGUIN ---");
    Serial.println(" [t] : launch test bench");
    Serial.println(" [s] : scan I2C bus");
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

    if (cameraDriver.begin())
    {
        Serial.println("CAM --initialized");
    }
    else
    {
        Serial.println("CAM init failure");
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

    motorL.begin(); 
    motorR.begin();
    hipL.begin(MotionConfig::DEFAULT_HIP_ANGLE, MotionConfig::MAX_HIP_ANGLE); 
    hipR.begin(MotionConfig::DEFAULT_HIP_ANGLE, MotionConfig::MAX_HIP_ANGLE); 

    behaviour.begin(); 
}

void loop()
{
    if (blinksRemaining > 0)
    {
        blinkP(activeBlinkPin, blinkCount);
    }

    runDash(); 

    scheduler.update(penguin_state);

    static uint32_t last = millis(); 
    uint32_t now = millis(); 

    float dt = (now - last) / 1000.0f; 
    last = now; 

    behaviour.update(penguin_commands, penguin_state, dt); 
    locomotion.update(penguin_state, penguin_commands, dt); 

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
}
