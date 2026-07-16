// fetch TELEMETRY data 

import {type PenguinData, type IMUData, DEFAULT_PENGUIN_DATA } from "../types";


function parseIMU(imu: any): IMUData { 
  return { 
    angles: { 
      pitch: imu.pitch, 
      roll: imu.roll, 
      yaw: imu.yaw, 
    }, 
    accX: imu.accX, 
    accY: imu.accY, 
    accZ: imu.accZ, 
    gyX: imu.gyX, 
    gyY: imu.gyY, 
    gyZ: imu.gyZ, 
    temp: imu.temp, 
  } 
} 

export default function parsePenguinData(data: any): PenguinData {
    return {
        ...DEFAULT_PENGUIN_DATA,
        imu: parseIMU(data.imu),
    };
}
