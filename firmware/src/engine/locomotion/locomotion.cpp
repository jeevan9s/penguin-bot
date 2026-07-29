/**
 * @file        locomotion.cpp
 * @brief       Implementation of core locomotion engine and controller orchestrator
 * @author      Jeevan Sanchez
 * @date        2026-07-27
 *
 * PENGUIN
 */

#pragma once

#include <Arduino.h>
#include "locomotion.hpp"

Locomotion::Locomotion(BalanceController &balance, VelocityController &wheelL, VelocityController &wheelR, MotorDriver &motorL, MotorDriver &motorR) 
: _balance(balance), _wheelL(wheelL, _wheelR(wheelR, _motorL(motorL), _motorR(motorR)) {}

void Locomotion::update(const penguin_state &state, const penguin_commands &commands, float dt) {
    
}