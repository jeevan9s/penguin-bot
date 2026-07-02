/**
 * @file        test_cam.cpp
 * @brief       OV2640 camera testing. 
 * @author      Jeevan Sanchez
 * @date        2026-07-01
 *
 * PENGUIN
 */

#include <Arduino.h>
#include "test_cam.hpp"
#include "esp_camera.h"\
#include "driver/ledc.h"


extern Adafruit_MCP23X17 mcp;


void startCameraClock() {
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .duty_resolution  = LEDC_TIMER_1_BIT,
        .freq_hz          = 20000000, // 20MHz XCLK
        .timer_num        = LEDC_TIMER_0
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel = {
        .gpio_num       = PIN_CAM_XCLK,
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_CHANNEL_0,
        .timer_sel      = LEDC_TIMER_0,
        .duty           = 1
    };
    ledc_channel_config(&ledc_channel);
}

void enable_cam() {
    Serial.println("launching cam startup sequence...");

    mcp.pinMode(Pins::MCP::CAM_PWR_EN, OUTPUT);
    mcp.digitalWrite(Pins::MCP::CAM_PWR_EN, HIGH);
    delay(100);

    mcp.pinMode(Pins::MCP::CAM_PWDN_EN, OUTPUT);
    mcp.digitalWrite(Pins::MCP::CAM_PWDN_EN, LOW);

    mcp.pinMode(Pins::MCP::CAM_RST, OUTPUT);
    mcp.digitalWrite(Pins::MCP::CAM_RST, LOW);
    delay(50);

    mcp.digitalWrite(Pins::MCP::CAM_RST, HIGH);
    delay(50);

    delay(50);
}

void setup_cam() {
    enable_cam();

    camera_config_t config; 

    config.pin_pwdn = -1;
    config.pin_reset = -1;

    config.pin_sccb_sda = Pins::MCU::SDA; 
    config.pin_sccb_scl = Pins::MCU::SCL;
    
    config.ledc_channel = LEDC_CHANNEL_0; 
    config.ledc_timer = LEDC_TIMER_0;

    config.pin_d0 = Pins::MCU::CAM_DATA_2; 
    config.pin_d1 = Pins::MCU::CAM_DATA_3;
    config.pin_d2 = Pins::MCU::CAM_DATA_4; 
    config.pin_d3 = Pins::MCU::CAM_DATA_5;
    config.pin_d4 = Pins::MCU::CAM_DATA_6;
    config.pin_d5 = Pins::MCU::CAM_DATA_7; 
    config.pin_d6 = Pins::MCU::CAM_DATA_8; 
    config.pin_d7 = Pins::MCU::CAM_DATA_9;
    
    config.pin_vsync = Pins::MCU::CAM_VSYNC; 
    config.pin_href = Pins::MCU::CAM_HREF; 

    config.pin_xclk = Pins::MCU::CAM_XCLK;
    config.pin_pclk = Pins::MCU::CAM_PCLK;

    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG; 
    config.frame_size = FRAMESIZE_QVGA; 
    config.jpeg_quality = 12;
    config.fb_count = 1;
    config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;

    Serial.println("launching camera driver...");
    esp_err_t err = esp_camera_init(&config);

    if (err != ESP_OK) {
        Serial.printf("camera init [FAILED]: 0x%x\n", err);
         blinkLED(Pins::MCP::DBG_LED, 1);
         blinkLED(Pins::MCP::CAM_LED, 1);
         blinkLED(Pins::MCP::DBG_LED, 2);
         return;
    }

    Serial.println("camera init [SUCCESS]");
    blinkLED(Pins::MCP::CAM_LED, 3);
    mcp.digitalWrite(Pins::MCP::CAM_LED, HIGH);
}

void test_cam() {

}