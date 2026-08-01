/**
 * @file        penguin_data.hpp
 * @brief       Global data definitions.
 * @author      Jeevan Sanchez
 * @date        2026-07-14
 *
 * PENGUIN
 */

#pragma once


/// @brief key rotational angles for PID balance controller & board visualization in dashboard
/// all angles are in degrees
struct Rotation 
{
    float pitch; 
    float roll; 
    float yaw;
};

// currently unused
enum struct health
{
    OFFLINE,
    INITIALIZED,
    ACTIVE,
    STANDBY
};

/// @brief IMU data structure containing three-axis acceleration readings, gyroscope rates, and temperature. 
/// magnetometer will be added as library is updated for Z-correction
struct IMUData
{
    float accX; // g 
    float accY;
    float accZ;

    float gyX; // dps
    float gyY;
    float gyZ;

    float temp; // C

    Rotation angles; 

};

/// @brief battery data structure for monitoring the 7.4V LiPo battery
// SOC needs an adjustment for clarity (SOC = State of Charge (%))
struct BattData
{
    float voltage;
    float SOC;
    bool connected;
};

/// @brief motor data structure for storing encoder data and ON/OFF tracking
struct MotorData
{
    long position; // encoder ticks 
    float RPM; 
    bool running; // true if motor is on
};

struct TOFData
{
    float proximity; // distance reading in mm
    bool obstacleDetected; // true based on threshold set in MotionConfig
};

// struct HealthData
// {
//     health imuStatus;
//     health camStatus;
//     health tofStatus;
// };12