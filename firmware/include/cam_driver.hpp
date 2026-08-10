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
#include "penguin_data.hpp"

#include "esp_camera.h"
#include "sensor.h"
#include "driver/ledc.h"
#include "esp_http_server.h"

extern Adafruit_MCP23X17 mcp;

/// @brief hardware driver class for the OV2640 camera (raw, no module)
/// based off of the esp_camera library
/// interfaces downstream with network/http_server
class CAMDriver
{
public:
    /// @brief camera and clock enable, camera configuration, I2C Wire management
    /// image parameter configuration (VGA, lower JPEG compression, higher contrast, default saturation, slightly sharper)
    /// @return true on successful init, false on failure
    bool begin();
    camera_fb_t *capture();
    void release(camera_fb_t *);

private:
    /// @brief probe the SCCB bus for an attached camera before attempting full initialization
    bool probe_camera();

    /// @brief enable the CAM power (AVDD = 2.8V, DOVDD = 1.2V, DVDD = 3.3V --with local LDOs), configure the camera power-down (PWDN) and reset pins
    void enable_cam();

    /// @brief setup an ledc timer channel @ 10MHz for the camera's XCLK
    void enable_clk();

    /// @brief initialization flag for the camera hardware
    bool camera_initialized = false;
};