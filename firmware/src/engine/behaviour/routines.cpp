/**
 * @file        routines.cpp
 * @brief       Sequenced primitive invocation with configurable constants
 * @author      Jeevan Sanchez
 * @date        2026-07-30
 *
 * PENGUIN
 */

#include <Arduino.h>
#include "routines.hpp"

Routine::Routine() : _currentRoutine(RoutineType::Default), _timer(0.0f), _step(0), _finished(false), _currentRPM(0.0f) {}

void Routine::setRoutine(RoutineType routine)
{
    if (_currentRoutine != routine)
    {
        _currentRoutine = routine;
        _step = 0;
        _timer = 0;
        _finished = false; 
    }
}

void Routine::update(PenguinCommands &commands, const PenguinState &state, float dt)
{
    _timer += dt;

    switch (_currentRoutine)
    {
    case RoutineType::Default:
        defaultRoutine(commands, state, dt);
        break;
    case RoutineType::Startup:
        startupRoutine(commands, state, dt);
        break;
    case RoutineType::Drive:
        driveRoutine(commands, state, dt);
        break;
    case RoutineType::ObstacleAvoidance:
        obstacleAvoidanceRoutine(commands, state, dt);
        break;
    case RoutineType::Patrol:
        patrolRoutine(commands, state, dt);
        break;
    default:
        defaultRoutine(commands, state, dt);
        break;
    }
}

// cycle between squat and standing for heartbeat behaviour
void Routine::defaultRoutine(PenguinCommands &commands, const PenguinState &state, float dt)
{
    if (_step == 0)
    {
        MotionPrimitives::squat(commands);
        _currentRPM = lerp(_currentRPM, 0.0f, RoutineConfig::SPEED_LERP_RATE, dt);
        MotionPrimitives::stop(commands);
        if (_timer >= RoutineConfig::DEFAULT_STEP_DURATION)
        {
            _step = 1;
            _timer = 0.0f;
        }
    }
    else if (_step == 1)
    {
        MotionPrimitives::stand(commands);
        _currentRPM = lerp(_currentRPM, 0.0f, RoutineConfig::SPEED_LERP_RATE, dt);
        MotionPrimitives::stop(commands);
        if (_timer >= RoutineConfig::DEFAULT_STEP_DURATION)
        {
            _step = 0;
            _timer = 0.0f;
            _finished = true; 
        }
    }
}

// PHASE 1: squat / pre-load
// PHASE 2: pause
// PHASE 3: standup while spinning
void Routine::startupRoutine(PenguinCommands &commands, const PenguinState &state, float dt)
{
    float targetRPM = 0.0f;

    switch (_step)
    {
    case 0:
        MotionPrimitives::squat(commands);
        targetRPM = 0.0f;
        if (_timer >= RoutineConfig::STARTUP_SQUAT_DURATION)
        {
            _step++;
            _timer = 0.0f;
        }
        break;

    case 1:
        MotionPrimitives::stop(commands);
        targetRPM = 0.0f;
        if (_timer >= RoutineConfig::STARTUP_PAUSE_DURATION)
        {
            _step++;
            _timer = 0.0f;
        }
        break;

    case 2:
        MotionPrimitives::stand(commands);
        targetRPM = MotionConfig::SPIN_STARTUP_SPEED;
        if (_timer >= RoutineConfig::STARTUP_SPIN_DURATION)
        {
            _step = 0;
            _timer = 0.0f;
            _finished = true;
        }
        break;
    }

    _currentRPM = lerp(_currentRPM, targetRPM, RoutineConfig::PIVOT_LERP_RATE, dt);
    if (_step == 2) {
        MotionPrimitives::turnLeft(commands, _currentRPM);
    }
}

// PHASE 1: CRUISE FORWARD
// PHASE 2: DROP SPEED & LOAD / CROUCH
// PHASE 3: TURBO
// PHASE 4: CRAWL FORWARD
void Routine::driveRoutine(PenguinCommands &commands, const PenguinState &state, float dt)
{
    float targetRPM = 0.0f;

    switch (_step)
    {
    case 0:
        targetRPM = getRPM(SpeedLevel::CRUISE);
        if (_timer >= RoutineConfig::DRIVE_CRUISE_DURATION)
        {
            _step++;
            _timer = 0.0f;
        }
        break;

    case 1:
        MotionPrimitives::squat(commands);
        targetRPM = getRPM(SpeedLevel::CRAWL);
        if (_timer >= RoutineConfig::DRIVE_SQUAT_DURATION)
        {
            _step++;
            _timer = 0.0f;
        }
        break;

    case 2:
        targetRPM = getRPM(SpeedLevel::TURBO);
        if (_timer >= RoutineConfig::DRIVE_TURBO_DURATION)
        {
            _step++;
            _timer = 0.0f;
        }
        break;

    case 3:
        MotionPrimitives::stand(commands);
        targetRPM = getRPM(SpeedLevel::CRAWL);
        if (_timer >= RoutineConfig::DRIVE_CRAWL_DURATION)
        {
            _step = 0;
            _timer = 0.0f;
            _finished = true; 
        }
        break;
    }

    _currentRPM = lerp(_currentRPM, targetRPM, RoutineConfig::SPEED_LERP_RATE, dt);
    MotionPrimitives::driveFWD(commands, _currentRPM);
}

// PHASE 1: CRUISE FORWARD
// PHASE 2: SCAN L/R
// PHASE 3: RETURN TO FORWARD CRUISE
void Routine::patrolRoutine(PenguinCommands &commands, const PenguinState &state, float dt)
{
    float targetRPM = 0.0f;

    switch (_step)
    {
    case 0:
        MotionPrimitives::stand(commands);
        targetRPM = getRPM(SpeedLevel::CRUISE);
        if (_timer >= RoutineConfig::PATROL_CRUISE_DURATION)
        {
            _step++;
            _timer = 0.0f;
        }
        break;

    case 1:
        if (scan(commands, MotionConfig::PIVOT_OFFST, dt))
        {
            _step++;
        }
        break;

    case 2:
        if (scan(commands, -MotionConfig::PIVOT_OFFST, dt))
        {
            _step++;
        }
        break;

    case 3:
        targetRPM = getRPM(SpeedLevel::CRUISE);
        if (_timer >= RoutineConfig::PATROL_CRUISE_DURATION)
        {
            _step = 0;
            _timer = 0.0f;
            _finished = true; 
        }
        break;
    }

    if (_step != 1 && _step != 2)
    {
        _currentRPM = lerp(_currentRPM, targetRPM, RoutineConfig::SPEED_LERP_RATE, dt);
        MotionPrimitives::driveFWD(commands, _currentRPM);
    }
}

// PHASE 1: EVASIVE SQUAT & REVERSE
// PHASE 2: SCAN L/R
// PHASE 3: RESUME FORWARD CRUISE
void Routine::obstacleAvoidanceRoutine(PenguinCommands &commands, const PenguinState &state, float dt)
{
    float targetRPM = 0.0f;

    switch (_step)
    {
    case 0:
        MotionPrimitives::squat(commands);
        targetRPM = getRPM(SpeedLevel::CRAWL);
        if (_timer >= RoutineConfig::EVASIVE_REVERSE_DURATION)
        {
            _step++;
            _timer = 0.0f;
        }
        break;

    case 1:
        if (scan(commands, MotionConfig::PIVOT_OFFST, dt))
        {
            _step++;
        }
        break;

    case 2:
        if (scan(commands, -MotionConfig::PIVOT_OFFST, dt))
        {
            _step++;
        }
        break;

    case 3:
        MotionPrimitives::stand(commands);
        targetRPM = getRPM(SpeedLevel::CRUISE);
        if (_timer >= RoutineConfig::EVASIVE_RECOVER_DURATION)
        {
            _step = 0;
            _timer = 0.0f;
            _finished = true; 
        }
        break;
    }

    if (_step == 0)
    {
        _currentRPM = lerp(_currentRPM, targetRPM, RoutineConfig::SPEED_LERP_RATE, dt);
        MotionPrimitives::driveREV(commands, _currentRPM);
    }
    else if (_step == 3)
    {
        _currentRPM = lerp(_currentRPM, targetRPM, RoutineConfig::SPEED_LERP_RATE, dt);
        MotionPrimitives::driveFWD(commands, _currentRPM);
    }
}

bool Routine::scan(PenguinCommands &commands, float pivotRPM, float duration)
{
    _currentRPM = lerp(_currentRPM, pivotRPM, RoutineConfig::PIVOT_LERP_RATE, 0.02f);
    MotionPrimitives::pivot(commands, _currentRPM);
    
    if (_timer >= duration)
    {
        _timer = 0.0f;
        return true;
    }
    return false;
}