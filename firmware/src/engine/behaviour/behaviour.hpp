/**
 * @file        behaviour.hpp
 * @brief       Class definition for routine manager --decision layer
 * @author      Jeevan Sanchez
 * @date        2026-07-30
 *
 * PENGUIN
 */

#pragma once 

#include <Arduino.h>
#include "routines.hpp"
#include "penguin_commands.hpp"
#include "penguin_state.hpp"

/// @brief routine manager class 
/// updates commands two-layers up
/// passes and tracks dt and timer down to routines
class Behaviour {
    public:
        Behaviour(); 

        /// @brief toggle the startup routine
        void begin();

        /// @brief toggle between the different routines
        /// this is moreso a test-point currently, trying out all the different routines
        /// intelligent behaviour routine will be implemented 
        void update(PenguinCommands &commands, const PenguinState &state, float dt); 

    private:
        /// @brief helper for routine-transitions
        /// @param next the routine to be changed to 
        void changeRoutine(RoutineType next); 
        Routine _routine;
        RoutineType _current; 
        float _timer; 
};
