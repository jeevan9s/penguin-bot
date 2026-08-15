/**
 * @file        scheduler.cpp
 * @brief       Telemetry event orchestration
 * @author      Jeevan Sanchez
 * @date        2026-07-18
 *
 *
 * PENGUIN
 */

#include <Arduino.h>
#include "scheduler.hpp"

Scheduler::Scheduler(IMUDriver &imu, BattDataDriver &batt,
                     TOFDriver &t1, TOFDriver &t2, TOFDriver &t3,
                     MotorDriver &m1, MotorDriver &m2)
    : _imu(imu), _batt(batt), _t1(t1), _t2(t2), _t3(t3), _m1(m1), _m2(m2),
      _imuTimer(10),   // 100 Hz
      _battTimer(500), // 2 Hz
      _tofTimer(40),   // 25 Hz
      _motorTimer(20)  // 50 Hz
{
}

void Scheduler::update(PenguinState &state)
{
    uint32_t now = millis();

    if (_imuTimer.expired(now))
    {
        state.imu = _imu.read();
    }

    if (_battTimer.expired(now))
    {
        state.battery = _batt.read();
    }

    if (_motorTimer.expired(now))
    {
        state.motorL = _m1.read();
        state.motorR = _m2.read();
    }

    if (_tofTimer.expired(now))
    {
        runTofSM(state);
    }
}

void Scheduler::runTofSM(PenguinState &state)
{
    if (_t1.ping())
    {
        state.sensL = _t1.read();
    }
    else
    {
        state.sensL.proximity = -1;
        state.sensL.obstacleDetected = false;
    }

    if (_t2.ping())
    {
        state.sensM = _t2.read();
    }
    else
    {
        state.sensM.proximity = -1;
        state.sensM.obstacleDetected = false;
    }

    if (_t3.ping())
    {
        state.sensR = _t3.read();
    }
    else
    {
        state.sensR.proximity = -1;
        state.sensR.obstacleDetected = false;
    }
}
