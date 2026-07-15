/**
 * @file        imu_driver.cpp
 * @brief       Implementation of IMU driver for communicating with the LSM6DSM. 
 * @author      Jeevan Sanchez
 * @date        2026-07-14
 *
 * PENGUIN
 */

#include "imu_driver.hpp"
#include "config.hpp"

bool begin() {
    if (!imu.init(0x6A, Wire)) return false; 
}

IMUData read() {
    IMUData _imu; 

    if (imu.dataReady()) {
            imu.readAll(); 

            _imu.accX = imu.accX(); 
            _imu.accY = imu.accY();
            _imu.accZ = imu.accZ();
            _imu.gyX = imu.gyX();
            _imu.gyY = imu.gyY();
            _imu.gyZ = imu.gyZ();
            _imu.accY = imu.accY(); 
            _imu.temp = imu.readTemp(); 

            Rotation angles = calculatePitch(imu.gyX, imu.gyY, imu.gyZ)

            _imu.angles = angles; 
    }


    return _imu; 
}

Rotation calculatePitch(float gx, float gy, float gz) {
    ///
    
}