// fetch TELEMETRY data 

import {type PenguinData, type IMUData, DEFAULT_PENGUIN_DATA, type BattData, type TOFData, type MotorData } from "../types";

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

function parseBattData(batt:any): BattData {
  batt = batt ?? {};
  return {
    voltage: batt.voltage ?? 0,
    SOC: batt.SOC ?? batt.soc ?? 0,
    connected: batt.connected ?? false,
  }
}

function parseTOFData(sens:any): TOFData {
  sens = sens ?? {};
  return {
    proximity: sens.proximity ?? 0,
    obstacleDetected: sens.obstacleDetected ?? false,
  }
}

function parseMotorData(motor:any): MotorData {
  return {
    position: motor.position, 
    RPM: motor.RPM, 
    running: motor.running,
  }
}

export default function parsePenguinData(data: any): PenguinData {
  const sensL = parseTOFData(data.sensL);
  const sensM = parseTOFData(data.sensM);
  const sensR = parseTOFData(data.sensR);

  const obsDetected = !!(
    sensL.obstacleDetected || sensM.obstacleDetected || sensR.obstacleDetected
  );

  return {
    ...DEFAULT_PENGUIN_DATA,
    imu: parseIMU(data.imu),
    battery: parseBattData(data.battery ?? data.batt),
    sensL,
    sensM,
    sensR,
    motorL: parseMotorData(data.motorL), 
    motorR: parseMotorData(data.motorR),
    obsDetected,
  };
}
