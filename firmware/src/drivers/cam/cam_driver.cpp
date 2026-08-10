/**
 * @file        cam_driver.cpp
 * @brief       Implementation of CAM driver for communicating with the OV2640.
 * @author      Jeevan Sanchez
 * @date        2026-07-14
 *
 * PENGUIN
 */

#include "cam_driver.hpp"

bool CAMDriver::begin()
{
    if (camera_initialized)
        return true;
    Wire.begin(Pins::MCU::SDA, Pins::MCU::SCL);
    Wire.setClock(100000);

    enable_clk();
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

    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;
    config.frame_size = FRAMESIZE_VGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
    config.grab_mode = CAMERA_GRAB_LATEST;
    esp_err_t err = esp_camera_init(&config);

    Wire.begin(Pins::MCU::SDA, Pins::MCU::SCL);
    Wire.setClock(100000);

    if (err != ESP_OK)
    {
        return false;
    }

    camera_initialized = true;

    sensor_t *s = esp_camera_sensor_get();
    s->set_framesize(s, FRAMESIZE_VGA);
    s->set_quality(s, 10);
    s->set_contrast(s, 1);
    s->set_saturation(s, 0);
    s->set_sharpness(s, 1);

    delay(1000);
    return true;
}

bool CAMDriver::probe_camera()
{
    static const uint8_t sccb_addresses[] = {0x30, 0x3C};

    Wire.begin(Pins::MCU::SDA, Pins::MCU::SCL);
    Wire.setClock(100000);
    delay(50);

    for (uint8_t addr : sccb_addresses)
    {
        Wire.beginTransmission(addr);
        uint8_t err = Wire.endTransmission();
        if (err == 0)
        {
            return true;
        }
        delay(5);
    }

    Wire.end();
    return false;
}

camera_fb_t *CAMDriver::capture()
{
    camera_fb_t *fb = esp_camera_fb_get(); // pointer to a frame buffer

    if (!fb)
        return nullptr; // capture failure

    return fb;
}

void CAMDriver::release(camera_fb_t *fb)
{
    if (fb)
        esp_camera_fb_return(fb);
}

void CAMDriver::enable_clk()
{
    ledc_timer_config_t ledc_timer;
    ledc_timer.speed_mode = LEDC_LOW_SPEED_MODE;
    ledc_timer.duty_resolution = LEDC_TIMER_1_BIT;
    ledc_timer.timer_num = LEDC_TIMER_0;
    ledc_timer.freq_hz = 10000000;
    ledc_timer.clk_cfg = LEDC_AUTO_CLK;
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel;
    ledc_channel.gpio_num = Pins::MCU::CAM_XCLK;
    ledc_channel.speed_mode = LEDC_LOW_SPEED_MODE;
    ledc_channel.channel = LEDC_CHANNEL_0;
    ledc_channel.intr_type = LEDC_INTR_DISABLE;
    ledc_channel.timer_sel = LEDC_TIMER_0;
    ledc_channel.duty = 1;
    ledc_channel.hpoint = 0;
    ledc_channel_config(&ledc_channel);
}

void CAMDriver::enable_cam()
{
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
