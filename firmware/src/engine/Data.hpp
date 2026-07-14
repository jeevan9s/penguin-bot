/**
 * @file        PenguinData.hpp
 * @brief       Global data definitions.
 * @author      Jeevan Sanchez
 * @date        2026-07-14
 *
 * PENGUIN
 */

namespace Penguin
{

    struct IMUData
    {
        float pitch;
        float roll;
        float yaw;

        float accX;
        float accY;
        float accZ;

        float gyX;
        float gyY;
        float gyZ;
    };

    struct BattData
    {
        float voltage;
        float SOC;
        bool connected;
    };

    struct MotorData
    {
        long position;
        float RPM;
        bool running;
    };

    struct TOFData 
    {
        float proximity; 
        bool obstacleDetected; 
        bool wheelSlipping;
    }; 

    struct HealthData
    {
        health imuStatus; 
        health camStatus; 
        health tofStatus; 
    
    };

}; 

enum health {
    OFFLINE, 
    INITIALIZED,
    ACTIVE, 
    STANDBY
}; 

