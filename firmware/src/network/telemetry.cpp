/**
 * @file        telemetry.hpp
 * @brief       Serialization file for streaming.  
 * @author      Jeevan Sanchez
 * @date        2026-07-15
 *
 * PENGUIN
 */

#include <Arduino.h>
#include "telemetry.hpp"

void Telemetry::serialize(const PenguinState &state, JsonDocument &doc) {
    doc["timestamp"] = millis(); 

    JsonObject imu = doc["imu"].to<JsonObject>();

    imu["pitch"] = state.imu.angles.pitch;
    imu["roll"] = state.imu.angles.roll;
    imu["yaw"] = state.imu.angles.yaw;
    
    imu["accX"] = state.imu.accX;
    imu["accY"] = state.imu.accY;
    imu["accZ"] = state.imu.accZ;

    imu["temp"] = state.imu.temp;
}