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
    JsonObject battery = doc["battery"].to<JsonObject>(); 
    JsonObject sensL = doc["sensL"].to<JsonObject>(); 
    JsonObject sensM = doc["sensM"].to<JsonObject>(); 
    JsonObject sensR = doc["sensR"].to<JsonObject>(); 
    JsonObject motorL = doc["motorL"].to<JsonObject>(); 
    JsonObject motorR = doc["motorR"].to<JsonObject>(); 
    

    imu["pitch"] = state.imu.angles.pitch;
    imu["roll"] = state.imu.angles.roll;
    imu["yaw"] = state.imu.angles.yaw;
    
    imu["accX"] = state.imu.accX;
    imu["accY"] = state.imu.accY;
    imu["accZ"] = state.imu.accZ;

    imu["temp"] = state.imu.temp;

    battery["voltage"] = state.battery.voltage; 
    battery["SOC"] = state.battery.SOC; 
    battery["connected"] = state.battery.connected; 

    sensL["proximity"] = state.sensL.proximity; 
    sensL["obstacleDetected"] = state.sensL.obstacleDetected;

    sensM["proximity"] = state.sensM.proximity; 
    sensM["obstacleDetected"] = state.sensM.obstacleDetected;

    sensR["proximity"] = state.sensR.proximity; 
    sensR["obstacleDetected"] = state.sensR.obstacleDetected;

    motorL["position"] = state.motorL.position; 
    motorL["RPM"] = state.motorL.RPM;
    motorL["running"] = state.motorL.running; 

    motorR["position"] = state.motorR.position; 
    motorR["RPM"] = state.motorR.RPM;
    motorR["running"] = state.motorR.running; 
}