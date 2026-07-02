/**
 * @file        test_bench.hpp
 * @brief       Header for test benchr.
 * @author      Jeevan Sanchez
 * @date        2026-06-29
 *
 * PENGUIN
 */

 #pragma once 

#include "config.h"

#include "test_leds.hpp"
#include "test_wifi.hpp"
#include "test_imu.hpp"
#include "test_pwr.hpp"
#include "test_cam.hpp"

// enum class TestMode = {
//     None, 
//     LEDS, 
//     WiFi, 
//     IMU
// };

void run_test_bench(); 