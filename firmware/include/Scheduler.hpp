/**
 * @file        Scheduler.hpp
 * @brief       Class definitions for event orchestration
 * @author      Jeevan Sanchez
 * @date        2026-07-18
 *
 *
 * PENGUIN
 */

#pragma once

#include <Arduino.h>
#include "state/PenguinState.hpp"
#include "imu_driver.hpp"
#include "cam_driver.hpp"
#include "batt_data_driver.hpp"
#include "tof_driver.hpp"
#include "motor_driver.hpp"

class Timer
{
public:
    Timer(uint32_t interval) : _interval(interval), _last(0) {}

    bool expired(uint32_t now)
    {
        if (now - _last >= _interval)
        {
            _last = now;
            return true;
        }
        return false;
    }

private:
    uint32_t _interval;
    uint32_t _last;
};

class Scheduler
{
public:
   Scheduler(IMUDriver &imu, BattDataDriver &batt, 
              TOFDriver &t1, TOFDriver &t2, TOFDriver &t3,
              MotorDriver &m1, MotorDriver &m2);
    void update(PenguinState &state);

private:
    IMUDriver &_imu;
    BattDataDriver &_batt;
    TOFDriver &_t1;
    TOFDriver &_t2;
    TOFDriver &_t3;
    MotorDriver &_m1;
    MotorDriver &_m2;

    Timer _imuTimer;
    Timer _battTimer;
    Timer _tofTimer;
    Timer _motorTimer;

    int _tofStep = 0;
    void runTofSM(PenguinState &state);
};