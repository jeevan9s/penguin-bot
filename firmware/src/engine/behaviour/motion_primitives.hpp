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
#include "motion_config.hpp"


class MotionPrimitives
{
public:

    static void stand(PenguinCommands& commands);

   static void squat(PenguinCommands& commands, int squatAngle = MotionConfig::SQUAT_HIP_ANGLE);

   static void leanFWD(PenguinCommands& commands);

   static void leanREV(PenguinCommands& commands);

   static void leanLeft(PenguinCommands& commands);

   static void leanRight(PenguinCommands& commands);

  static void stop(PenguinCommands& commands); 

   static void pivot(PenguinCommands& commands, float rpm); 
    
   static void driveFWD(PenguinCommands& commands, float rpm);

    static void driveREV(PenguinCommands& commands, float rpm);

   static void turnLeft(PenguinCommands& commands, float rpm);

   static void turnRight(PenguinCommands& commands, float rpm);

private:

    // float _jumpTimer = 0.0f;
};

