/**
 * @file        routines.hpp
 * @brief       Sequenced primitive invocation
 * @author      Jeevan Sanchez
 * @date        2026-07-30
 *
 * PENGUIN
 */

#pragma once

#include <Arduino.h>
#include "motion_primitives.hpp"
#include "penguin_commands.hpp"
#include "penguin_state.hpp"

#pragma once

enum class RoutineType
{
    Default,
    Startup,
    Drive,
    // Recovery,
    Patrol,
    ObstacleAvoidance
};


class Routine
{
public:

    Routine();

    void setRoutine(RoutineType routine);

    void update(
        PenguinCommands& commands,
        const PenguinState& state,
        float dt
    );

    bool _finished;


private:

    void defaultRoutine(
        PenguinCommands& commands,
        const PenguinState& state,
        float dt
    );

    void startupRoutine(
        PenguinCommands& commands,
        const PenguinState& state,
        float dt
    );

    void driveRoutine(
        PenguinCommands& commands,
        const PenguinState& state,
        float dt
    );

    void patrolRoutine(
        PenguinCommands& commands,
        const PenguinState& state,
        float dt
    );

    void obstacleAvoidanceRoutine(
        PenguinCommands& commands,
        const PenguinState& state,
        float dt
    );

    RoutineType _currentRoutine;

    MotionPrimitives _primitives;

    bool scan(PenguinCommands &commands, float pivotRPM, float duration=1.5f);

    uint8_t _step;
    float _timer;
};