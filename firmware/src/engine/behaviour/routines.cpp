/**
 * @file        routines.cpp
 * @brief       Sequenced primitive invocation
 * @author      Jeevan Sanchez
 * @date        2026-07-30
 *
 * PENGUIN
 */

#include <Arduino.h>
#include "routines.hpp"

Routine::Routine() : _currentRoutine(RoutineType::Default), _timer(0.0f), _step(0) {}

Routine::setRoutine(RoutineType routine)
{
    if (_currentRoutine != routine)
    {
        _currentRoutine = routine;
        _step = 0;
        _timer = 0;
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
        defaultRoutine(commands, state, dt);
        break;

    case RoutineType::Drive:
        defaultRoutine(commands, state, dt);
        break;

    case RoutineType::ObstacleAvoidance:
        defaultRoutine(commands, state, dt);
        break;

    case RoutineType::Patrol:
        defaultRoutine(commands, state, dt);
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
        MotionPrimitives::stop(commands);
        if (_timer >= 3.0f)
        {
            _step = 1;
            _timer = 0.0f;
        }
    }

    if (_step == 1)
    {
        MotionPrimitives::stand(commands);
        MotionPrimitives::stop(commands);
        if (_timer >= 3.0f)
        {
            _step = 0;
            _timer = 0.0f;
        }
    }
}

// PHASE 1: squat / pre-load
// PHASE 2: pause
// PHASE 3: standup while spinning
void Routine::startupRoutine(PenguinCommands &commands, const PenguinState &state, float dt)
{
    switch (_step)
    {
    case 0:
        MotionPrimitives::squat(commands);
        if (_timer >= 0.5f)
        {
            _step++;
            _timer = 0.0f;
        }
        break;

    case 1:
        MotionPrimitives::stop(commands);
        if (timer >= 0.5f)
        {
            _step++;
            _timer = 0.0f;
        }
        break;

    case 2:
        MotionPrimitives::stand(commands);
        MotionPrimitives::turnLeft(commands, MotionConfig::SPIN_STARTUP_SPEED);
        if (timer >= 3.0f)
        {
            _step = 0;
            _timer = 0.0f;
        }
        break;
    }
}

// PHASE 1: CRUISE FORWARD
// PHASE 2: DROP SPEED & LOAD / CROUCH
// PHASE 3: TURBO
// PHASE 4: CRAWL FORWARD
void Routine::driveRoutine(PenguinCommands &commands, const PenguinState &state, float dt)
{

    switch (_step)
    {
    case 0:
        MotionPrimitives::driveFWD(commands, getRPM(SpeedLevel::CRUISE));
        if (_timer >= 5.0f)
        {
            _step++;
            _timer = 0.0;
        }
        break;

    case 1:
        MotionPrimitives::squat(commands);
        MotionPrimitives::driveFWD(commands, getRPM(SpeedLevel::CRAWL));
        if (_timer >= 2.5f)
        {
            _step++;
            _timer = 0.0f;
        }
        break;

    case 2:
        MotionPrimitives::driveFWD(commands, getRPM(SpeedLevel::TURBO));
        if (_timer >= 2.0f)
        {
            _step++;
            _timer = 0.0f;
        }
        break;

    case 3:
        MotionPrimitives::stand(commands);
        MotionPrimitives::driveFWD(commands, getRPM(SpeedLevel::CRAWL));
        if (_timer >= 5.0f)
        {
            _step = 0;
            _timer = 0.0f;
        }
    }
}

// PHASE 1: CRUISE FORWARD
// PHASE 2: SCAN L/R
// PHASE 3: RETURN TO FORWARD CRUISE
void Routine::patrolRoutine(commands)
{
    switch (_step)
    {
    case 0:
        MotionPrimitives::stand(commands);
        MotionPrimitives::driveFWD(commands, getRPM(SpeedLevel::CRUISE));
        if (_timer >= 4.0f)
        {
            _step++;
            _timer = 0.0f;
        }
        break;

    case 1:
        if (scan(commands, MotionConfig::PIVOT_OFFST))
        {
            _step++;
        }
        break;

    case 2:
        if (scan(commands, -MotionConfig::PIVOT_OFFST))
        {
            _step++;
        }
        break;

    case 3:
        MotionPrimitives::driveFWD(commands, getRPM(SpeedLevel::CRUISE));
        if (_timer >= 4.0f)
        {
            _step = 0;
            _timer = 0.0f;
        }
        break;
    }
}

// PHASE 1: EVASIVE SQUAT & REVERSE
// PHASE 2: SCAN L/R
// PHASE 3: RESUME FORWARD CRUISE
void Routine::obstacleAvoidanceRoutine(PenguinCommands &commands, const PenguinState &state, float dt)
{
    switch (_step)
    {
    case 0:
        MotionPrimitives::squat(commands);
        MotionPrimitives::driveREV(commands, getRPM(SpeedLevel::CRAWL));
        if (_timer >= 2.0f)
        {
            _step++;
            _timer = 0.0f;
        }
        break;

    case 1:
        if (scan(commands, MotionConfig::PIVOT_OFFST))
        {
            _step++;
        }
        break;

    case 2:
        if (scan(commands, -MotionConfig::PIVOT_OFFST))
        {
            _step++;
        }
        break;

    case 3:
        MotionPrimitives::stand(commands);
        MotionPrimitives::driveFWD(commands, getRPM(SpeedLevel::CRUISE));
        if (_timer >= 2.0f)
        {
            _step = 0;
            _timer = 0.0f;
        }
        break;
    }
}

bool Routine::scan(PenguinCommands &commands, float pivotRPM, float duration)
{
    MotionPrimitives::pivot(commands, pivotRPM);
    if (_timer >= duration)
    {
        _timer = 0.0f;
        return true;
    }
    return false;
}