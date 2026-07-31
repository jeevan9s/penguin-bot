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

Behaviour::Behaviour() : _routine(), _timer(0.0f), _current(RoutineType::Default) {} 

void Behaviour::begin() {
    changeRoutine(RoutineType::Startup); 

}

void Behaviour::update(PenguinCommands &commands, const PenguinState &state, float dt) {
    
    // obstacle avoidance @ highest priority 
    if (state.sensL.obstacleDetected || state.sensM.obstacleDetected || state.sensR.proximity) {
        changeRoutine(RoutineType::ObstacleAvoidance); 
    }

    // default -> drive
    else if (_current == RoutineType::Startup && _routine._finished) {
        changeRoutine(RoutineType::Default); 
    }

    else if (_current == RoutineType::Default && _routine._finished) {
        changeRoutine(RoutineType::Drive); 
    }

    // drive -> patrol
    else if (_current == RoutineType::Drive && _routine._finished) {
        changeRoutine(RoutineType::Patrol); 
    }

    // patrol -> default
    else if (_current == RoutineType::Patrol && _routine._finished) {
        changeRoutine(RoutineType::Default); 
    }

    // obstacle avoidance done
    else if (_current == RoutineType::ObstacleAvoidance && _routine._finished) {
        changeRoutine(RoutineType::Patrol); 
    }

    _routine.update(commands, state, dt); 
}

void Behaviour::changeRoutine(RoutineType next) {
    if (next == _current) return; 
    _current = next; 
    _routine.setRoutine(next); 
}