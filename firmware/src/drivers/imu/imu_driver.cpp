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

        c_angles = calculateAngles(imu.gyX(), imu.gyY(), imu.gyZ(),imu.accX(), imu.accY(), imu.accZ());

        _imu.angles = c_angles;
    }
    return _imu;
}

Rotation IMUDriver::calculateAngles(float gx, float gy, float gz, float ax, float ay, float az)
{
    uint32_t current_time = millis();
    float dt = (current_time - last_timestamp) / 1000.0f;
    last_timestamp = current_time;

    if (dt > 0.1f)
        dt = 0.01f; // handle lag spikes

    // accelerometer-derived tilt 
    float accel_pitch = atan2(ay, sqrt(ax * ax + az * az)) * 180.0f / PI;
    float accel_roll  = atan2(-ax, az) * 180.0f / PI;

    // gyro integration 
    float gyro_pitch = c_angles.pitch + gx * dt;
    float gyro_roll  = c_angles.roll + gy * dt;

    // filter: mostly trust gyro short-term, slowly correct with accel
    const float alpha = 0.98f;
    c_angles.pitch = alpha * gyro_pitch + (1.0f - alpha) * accel_pitch;
    c_angles.roll  = alpha * gyro_roll  + (1.0f - alpha) * accel_roll;

    c_angles.yaw += gz * dt;

    return c_angles;
}