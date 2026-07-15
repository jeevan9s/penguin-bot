/**
 * @file        cam_driver.hpp
 * @brief       Header for CAM driver to stream from the OV2640. 
 * @author      Jeevan Sanchez
 * @date        2026-07-14
 *
 * PENGUIN
 */

#pragma once 

#include <Arduino.h>
#include "config.hpp"
#include "PenguinData.hpp"

#include "esp_camera.h"
#include "sensor.h"
#include "driver/ledc.h"
#include "esp_http_server.h"

class CAMDriver {
    public:
        bool begin(); 
        bool capture(); 

    private:
        void enable_cam(); 
        void enable_clk(); 
};