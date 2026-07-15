/**
 * @file        imu_driver.cpp
 * @brief       Implementation of IMU driver for communicating with the LSM6DSM.
 * @author      Jeevan Sanchez
 * @date        2026-07-14
 *
 * PENGUIN
 */

#include <Arduino.h>
#include "imu_driver.hpp"
#include "config.hpp"

bool IMUDriver::begin()
{
    if (!imu.init(0x6A, Wire))
        return false;

    last_timestamp = millis();
    return true;
}

IMUData IMUDriver::read()
{
    IMUData _imu;

    if (imu.dataReady())
    {
        imu.readAll();

        _imu.accX = imu.accX();
        _imu.accY = imu.accY();
        _imu.accZ = imu.accZ();
        _imu.gyX = imu.gyX();
        _imu.gyY = imu.gyY();
        _imu.gyZ = imu.gyZ();
        _imu.temp = imu.readTemp();

        angles = calculateAngles(imu.gyX(), imu.gyY(), imu.gyZ());

        _imu.angles = angles;
    }
    return _imu;
}

Rotation IMUDriver::calculateAngles(float gx, float gy, float gz)
{
    uint32_t current_time = millis();
    float dt = (current_time - last_timestamp) / 1000.0f;
    last_timestamp = current_time;

    if (dt > 0.1f)
        dt = 0.01f; // handle lag spikes

    c_angles.pitch += gx * dt;
    c_angles.roll += gy * dt;
    c_angles.yaw += gz * dt;

    return c_angles;
}