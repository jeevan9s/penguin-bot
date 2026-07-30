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

class MotionPrimitive
{
public:
    virtual ~MotionPrimitive() = default;

    virtual void update(
        PenguinCommands &commands,
        const PenguinState &state,
        float dt) = 0;
};
