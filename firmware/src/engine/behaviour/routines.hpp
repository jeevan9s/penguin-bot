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


/// Routines are sequences of Motion Primitives
/// Routines update commands Internally through primitives
/// Routines used non-blocking timer-incrementation and step-counting between primitives

/// @brief all of the robot's CURRENT possible routines 
/// Recovery is not implemented yet, it would be invoked based on some PenguinState flag for fallen. 
enum class RoutineType
{
    Default,
    Startup,
    Drive,
    // Recovery,
    Patrol,
    ObstacleAvoidance
};


/// @brief parent routine structure owning all routines defined in the enum above
class Routine
{
public:

    Routine();

    /// @brief trigger a routine
    /// @param routine the routine to be triggered 
    void setRoutine(RoutineType routine);

    /// @brief updates active state machine routine and increments timer 
    /// @param commands global commands instance
    /// @param state global state instance
    /// @param dt delta-time elapsed since last update frame
    void update(
        PenguinCommands& commands,
        const PenguinState& state,
        float dt
    );

    /// @brief tracking member for routine completion
    /// set true at the end of each routine, and false in setRoutine();
    bool _finished;


private:

    /// @brief heartbeat routine 
    void defaultRoutine(
        PenguinCommands& commands,
        const PenguinState& state,
        float dt
    );

    /// @brief squats, spins & stands -- startup motion-jingle
    void startupRoutine(
        PenguinCommands& commands,
        const PenguinState& state,
        float dt
    );

    /// @brief general drive routine cycling between different speeds 
    void driveRoutine(
        PenguinCommands& commands,
        const PenguinState& state,
        float dt
    );

    /// @brief drive routine with frequent L/R scanning (pivot)
    void patrolRoutine(
        PenguinCommands& commands,
        const PenguinState& state,
        float dt
    );


    /// @brief duck and reverse, continue patrol
    /// invoked based on sensor values
    void obstacleAvoidanceRoutine(
        PenguinCommands& commands,
        const PenguinState& state,
        float dt
    );

    RoutineType _currentRoutine;

    MotionPrimitives _primitives;

    /// @brief helper for pivot & stand motion (a scan -- for ToF sensors)
    bool scan(PenguinCommands &commands, float pivotRPM, float duration=1.5f);

    uint8_t _step;
    float _timer;
};
