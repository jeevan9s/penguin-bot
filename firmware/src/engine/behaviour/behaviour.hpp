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

class Behaviour {
    public:
        Behaviour(); 
        void begin();

        void update(PenguinCommands &commands, const PenguinState &state, float dt); 

    private:
        void changeRoutine(RoutineType next); 
        Routine _routine;
        RoutineType _current; 
        float _timer; 
};
