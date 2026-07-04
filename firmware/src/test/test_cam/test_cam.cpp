/**
 * @file        test_cam.cpp
 * @brief       OV2640 camera testing. 
 * @author      Jeevan Sanchez
 * @date        2026-07-01
 *
 * PENGUIN
 */

#include <Arduino.h>
#include <Wire.h>
#include "test_cam.hpp"
#include "pinouts.hpp"
#include "esp_camera.h"
#include "sensor.h"
#include "driver/ledc.h"
#include "mbedtls/base64.h"

extern Adafruit_MCP23X17 mcp;

void startCameraClock() {
    ledc_timer_config_t ledc_timer; 
    ledc_timer.speed_mode       = LEDC_LOW_SPEED_MODE; 
    ledc_timer.duty_resolution  = LEDC_TIMER_1_BIT;    
    ledc_timer.timer_num        = LEDC_TIMER_0;        
    ledc_timer.freq_hz          = 10000000;
    ledc_timer.clk_cfg          = LEDC_AUTO_CLK;       
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel; 
    ledc_channel.gpio_num       = Pins::MCU::CAM_XCLK; 
    ledc_channel.speed_mode     = LEDC_LOW_SPEED_MODE; 
    ledc_channel.channel        = LEDC_CHANNEL_0;      
    ledc_channel.intr_type      = LEDC_INTR_DISABLE;   
    ledc_channel.timer_sel      = LEDC_TIMER_0;        
    ledc_channel.duty           = 1;
    ledc_channel.hpoint         = 0;
    ledc_channel_config(&ledc_channel);
}

void enable_cam() {
    Serial.println("launching cam startup sequence...");
    mcp.pinMode(Pins::MCP::CAM_PWR_EN, OUTPUT);
    mcp.digitalWrite(Pins::MCP::CAM_PWR_EN, LOW);
    delay(200);
    mcp.digitalWrite(Pins::MCP::CAM_PWR_EN, HIGH);
    delay(200);

    mcp.pinMode(Pins::MCP::CAM_PWDN_EN, OUTPUT);
    mcp.digitalWrite(Pins::MCP::CAM_PWDN_EN, LOW);

    mcp.pinMode(Pins::MCP::CAM_RST, OUTPUT);
    mcp.digitalWrite(Pins::MCP::CAM_RST, LOW);
    delay(50);
    mcp.digitalWrite(Pins::MCP::CAM_RST, HIGH);
    delay(50);
}

void setup_cam() {
    Wire.begin(Pins::MCU::SDA, Pins::MCU::SCL);
    Wire.setClock(100000);

    startCameraClock();
    recoverI2C();
    enable_cam();

    Wire.end();
    delay(200);

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

    config.xclk_freq_hz = 10000000;
    config.pixel_format = PIXFORMAT_JPEG;
    config.frame_size = FRAMESIZE_VGA;
    config.jpeg_quality = 10;
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

    sensor_t * s = esp_camera_sensor_get();
    s->set_framesize(s, FRAMESIZE_VGA); 
    s->set_quality(s, 10);
    s->set_contrast(s, 1);
    s->set_saturation(s, 0);
    s->set_sharpness(s, 1);
    
    delay(1000);

    Serial.println("camera init [SUCCESS]");
}

void test_cam() {
    for(int i = 0; i < 3; i++) {
        camera_fb_t * fb = esp_camera_fb_get();
        if (fb) esp_camera_fb_return(fb);
    }

    camera_fb_t * fb = esp_camera_fb_get();
    if (!fb) {
        Serial.println("Capture failed");
        return;
    }

    size_t olen = 0;
    size_t output_len = (fb->len * 4 / 3) + 4;
    char * output = (char *)malloc(output_len);

    if (output && mbedtls_base64_encode((unsigned char *)output, output_len, &olen, (const unsigned char *)fb->buf, fb->len) == 0) {
        Serial.println("\n--- START IMAGE ---");
        Serial.write((uint8_t*)output, olen);
        Serial.println("\n--- END IMAGE ---");
    }

    free(output);
    esp_camera_fb_return(fb);
}