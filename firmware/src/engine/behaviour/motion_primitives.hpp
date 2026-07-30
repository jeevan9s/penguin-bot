/**
 * @file        motion_primitives.hpp
 * @brief       Base class definition and individual declarations for motion primitives (movement actions)
 * @author      Jeevan Sanchez
 * @date        2026-07-30
 *
 * PENGUIN
 */

#pragma once

#include <Arduino.h>
#include "penguin_commands.hpp"
#include "penguin_state.hpp"


class MotionPrimitives
{
public:

    void stand(PenguinCommands& commands);

    void squat(PenguinCommands& commands);

    void leanFWD(PenguinCommands& commands);

    void leanREV(PenguinCommands& commands);

    void leanLeft(PenguinCommands& commands);

    void leanRight(PenguinCommands& commands);

    void driveFWD(PenguinCommands& commands, float rpm);

    void driveREV(PenguinCommands& commands, float rpm);

    void turnLeft(PenguinCommands& commands, float rpm);

    void turnRight(PenguinCommands& commands, float rpm);

    void spinClockwise(PenguinCommands& commands, float rpm);

    void spinCounterClockwise(PenguinCommands& commands, float rpm);
    

private:

    // float _jumpTimer = 0.0f;
};