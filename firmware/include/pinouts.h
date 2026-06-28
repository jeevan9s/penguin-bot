/**
 * @file        pinouts.h
 * @brief       System pin definitions and hardware mappings.
 * @author      Jeevan Sanchez
 * @date        2026-06-28
 * 
 * PENGUIN
 */

 
 #include <cstdint>

namespace Pins {
    namespace MCU {
        constexpr uint8_t SCL = 1;
        constexpr uint8_t SDA = 2; 
        constexpr uint8_t CAM_XCLK = 3; 
        constexpr uint8_t VBATT_SENSE = 4; 
        constexpr uint8_t R_SERVO = 5;
        constexpr uint8_t L_SERVO = 6; 
        constexpr uint8_t CAM_VSYNC = 7;
        constexpr uint8_t ENC_A_PH2 = 8; 
        constexpr uint8_t CAM_DATA_9 = 9;
        constexpr uint8_t CAM_DATA_8 = 10; 
        constexpr uint8_t CAM_DATA_7 = 11; 
        constexpr uint8_t CAM_DATA_6 = 12;
        constexpr uint8_t CAM_DATA_2 = 13;
        constexpr uint8_t CAM_DATA_5 = 14; 
        constexpr uint8_t CAM_HREF = 15;
        constexpr uint8_t ENC_B_PH1 = 16;
        constexpr uint8_t ENC_B_PH2 = 17;
        constexpr uint8_t ENC_A_PH1 = 18; 
        constexpr uint8_t CAM_DATA_3 = 21;
        constexpr uint8_t MOTA_IN1 = 38;
        constexpr uint8_t MOTA_IN2 = 39;
        constexpr uint8_t MOTB_IN1 = 40;
        constexpr uint8_t MOTB_IN2 = 41;
        constexpr uint8_t MCP_RESET = 42; 
        constexpr uint8_t CAM_DATA_4 = 47; 
        constexpr uint8_t CAM_PCLK = 48;
    }

    // MCP23017 IO expander
    namespace MCP {
        constexpr uint8_t DBG_LED       = 0;  // GPA0
        constexpr uint8_t WIFI_LED      = 1;  // GPA1
        constexpr uint8_t CAM_LED    = 2;  // GPA2
        constexpr uint8_t RGB_DATA      = 3;  // GPA3
        constexpr uint8_t BUZZ_EN       = 4;  // GPA4
        constexpr uint8_t CAM_PWR_EN       = 5;  // GPA5
        constexpr uint8_t CAM_PWDN_EN   = 6;  // GPA6
        constexpr uint8_t CAM_RST       = 7;  // GPA7

        constexpr uint8_t DRV_FAULT     = 11; // GPB3
        constexpr uint8_t VMOT_EN       = 12; // GPB4
        constexpr uint8_t TOF_XSHUT_1   = 13; // GPB5
        constexpr uint8_t TOF_XSHUT_2   = 14; // GPB6
        constexpr uint8_t TOF_XSHUT_3   = 15; // GPB7
    }
}