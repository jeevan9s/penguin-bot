interface Rotation  {
    pitch: number; 
    roll: number; 
    yaw: number; 
}

export interface IMUData  {
    angles: Rotation; 

    accX: number;
    accY: number; 
    accZ: number; 

    gyX: number; 
    gyY: number;
    gyZ: number; 

    temp: number;
}; 

export interface BattData  {
    voltage: number; 
    soc: number; 
    connected: boolean;
}

export interface MotorData  {
    position: number; 
    rpm: number; 
    running: boolean;
}

export interface TOFData  {
    proximity: number; 
    obstacleDetected: boolean; 
    wheelSlipping: boolean;
}


export interface PenguinData {
    imu: IMUData;  
    
    battery: BattData; 

    motorA: MotorData; 
    motorB: MotorData; 

    sensL: TOFData; 
    sensM: TOFData; 
    sensR: TOFData;
}

export const DEFAULT_ESP_IP = "10.0.0.169";

export const DEFAULT_PENGUIN_DATA: PenguinData = {
    imu: {
        angles: {
            pitch: 0,
            roll: 0,
            yaw: 0,
        },

        accX: 0,
        accY: 0,
        accZ: 0,

        gyX: 0,
        gyY: 0,
        gyZ: 0,

        temp: 0,
    },

    battery: {
        voltage: 0,
        soc: 0,
        connected: false,
    },

    motorA: {
        position: 0,
        rpm: 0,
        running: false,
    },

    motorB: {
        position: 0,
        rpm: 0,
        running: false,
    },

    sensL: {
        proximity: 0,
        obstacleDetected: false,
        wheelSlipping: false,
    },

    sensM: {
        proximity: 0,
        obstacleDetected: false,
        wheelSlipping: false,
    },

    sensR: {
        proximity: 0,
        obstacleDetected: false,
        wheelSlipping: false,
    },
};