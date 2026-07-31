/**
 * @file        behaviour.cpp
 * @brief       Implementation for routine manager --decision layer
 * @author      Jeevan Sanchez
 * @date        2026-07-31
 *
 * PENGUIN
 */

#include <Arduino.h>
#include "behaviour.hpp"

Behaviour::Behaviour() : _routine(), _timer(0.0f), _current(RoutineType::Default); 

void Behaviour::begin() {
    _current = RoutineType::Startup; 
    _routine.setRoutine(_current); 
}

void Behaviour::update(PenguinCommands &commands, const PenguinState &state, float dt) {
    

}

void Behaviour::changeRoutine(RoutineType next) {
    if (next == _current) return; 

    _current = next; 
    _routine.setRoutine(next); 
}