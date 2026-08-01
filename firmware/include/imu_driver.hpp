/**
 * @file        imu_driver.hpp
 * @brief       Header for IMU driver to communicate with the LSM6DSM.
 * Based off the library in https://github.com/jeevan9s/device-libs
 * @author      Jeevan Sanchez
 * @date        2026-07-14
 *
 * PENGUIN
 */

#pragma once

#include <Arduino.h>
#include <LSM6DSM/src/LSM6DSM.h>
#include "penguin_data.hpp"

extern LSM6DSM imu;

/// @brief hardware driver for the LSM6MDSM IMU
class IMUDriver
{
public:
    /// @brief setup with global I2C Wire reference and initiailize timer for core angle calculations
    /// @return true on successful IMU init, false on failure
    bool begin();

    /// @brief populate the IMUData structure with read values and filtered and calculated core angles (pitch, roll, yaw)
    /// @return populated IMUData structure for downstream telemetry and PID control
    IMUData read();

private:
    /// @brief calculates pitch roll and yaw using a complementary filter
    /// @param gx gyroscope x-axis angular velocity
    /// @param gy gyroscope y-axis angular velocity
    /// @param gz gyroscope z-axis angular velocity
    /// @param ax accelerometer x-axis acceleration
    /// @param ay accelerometer y-axis acceleration
    /// @param az accelerometer z-axis acceleration
    /// @return combined orientation angles struct
    Rotation calculateAngles(float gx, float gy, float gz, float ax, float ay, float az);

    /// @brief core angles initializaed as zero
    Rotation c_angles = {0.0f, 0.0f, 0.0f};

    // for deriving angles from angular rates (gx, gy, gz)
    uint32_t last_timestamp = 0; // ms
};