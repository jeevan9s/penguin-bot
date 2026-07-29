/**
 * @file        imu_driver.hpp
 * @brief       Header for IMU driver to communicate with the LSM6DSM. 
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

class IMUDriver {
    public:
        bool begin(); 
        IMUData read(); 

    private:
        Rotation calculateAngles(float gx, float gy, float gz, float ax, float ay, float az); 
        Rotation c_angles = {0.0f, 0.0f, 0.0f};
        uint32_t last_timestamp = 0; // ms
};