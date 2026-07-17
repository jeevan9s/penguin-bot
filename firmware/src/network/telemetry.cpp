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
    JsonObject batt = doc["batt"].to<JsonObject>(); 
    JsonObject sensL = doc["sensL"].to<JsonObject>(); 
    JsonObject sensM = doc["sensM"].to<JsonObject>(); 
    JsonObject sensR = doc["sensR"].to<JsonObject>(); 

    imu["pitch"] = state.imu.angles.pitch;
    imu["roll"] = state.imu.angles.roll;
    imu["yaw"] = state.imu.angles.yaw;
    
    imu["accX"] = state.imu.accX;
    imu["accY"] = state.imu.accY;
    imu["accZ"] = state.imu.accZ;

    imu["temp"] = state.imu.temp;

    batt["voltage"] = state.battery.voltage; 
    batt["SOC"] = state.battery.SOC; 
    batt["connected"] = state.battery.connected; 

    sensL["proximity"] = state.sensL.proximity; 
    sensL["obstacleDetected"] = state.sensL.obstacleDetected;

    sensM["proximity"] = state.sensM.proximity; 
    sensM["obstacleDetected"] = state.sensM.obstacleDetected;

    sensR["proximity"] = state.sensR.proximity; 
    sensR["obstacleDetected"] = state.sensR.obstacleDetected;
}