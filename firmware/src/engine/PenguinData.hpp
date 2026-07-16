/**
 * @file        PenguinData.hpp
 * @brief       Global data definitions.
 * @author      Jeevan Sanchez
 * @date        2026-07-14
 *
 * PENGUIN
 */

#pragma once

struct Rotation 
{
    float pitch; 
    float roll; 
    float yaw;
};

enum struct health
{
    OFFLINE,
    INITIALIZED,
    ACTIVE,
    STANDBY
};


struct IMUData
{
    float accX;
    float accY;
    float accZ;

    float gyX;
    float gyY;
    float gyZ;

    float temp; 

    Rotation angles; 

};

struct BattData
{
    float voltage;
    float SOC;
    bool connected;
};

struct MotorData
{
    long position;
    float RPM;
    bool running;
};

struct TOFData
{
    float proximity;
    bool obstacleDetected;
    bool wheelSlipping;
};

struct HealthData
{
    health imuStatus;
    health camStatus;
    health tofStatus;
};