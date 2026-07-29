/**
 * @file        locomotion.cpp
 * @brief       Implementation of core locomotion engine and controller orchestrator
 * @author      Jeevan Sanchez
 * @date        2026-07-27
 *
 * PENGUIN
 */


#include <Arduino.h>
#include "locomotion.hpp"

Locomotion::Locomotion(BalanceController &balance, VelocityController &leftVController, VelocityController &rightVController, MotorDriver &motorL, MotorDriver &motorR, ServoDriver &hipL, ServoDriver &hipR) 
: _balance(balance), _leftVController(leftVController), _rightVController(rightVController), _motorL(motorL), _motorR(motorR), _hipL(hipL), _hipR(hipR) {}

void Locomotion::update(const PenguinState &state, const PenguinCommands &commands, float dt) {
    float balanceOutput = _balance.update(state.imu, commands.targetPitch, dt); 

    WheelTargets targets = calculateWheelTargets(commands, balanceOutput);

    float leftPWM = _leftVController.update(state.motorL, targets.leftRPM, dt); 
    float rightPWM = _rightVController.update(state.motorR, targets.rightRPM, dt); 

    _motorL.run(leftPWM); 
    _motorR.run(leftPWM);     

    _hipL.write(commands.leftHipAngle); 
    _hipR.write(commands.rightHipAngle); 
}

// L/R_SPEED = FWD_INPUT - TURN_INPUT + CORRECTION_INPUT
WheelTargets Locomotion::calculateWheelTargets(const PenguinCommands &commands, float balanceOutput) {
    WheelTargets targets; 

    targets.leftRPM = commands.forwardRPM - commands.turnRPM + balanceOutput; 
    targets.rightRPM = commands.forwardRPM - commands.turnRPM + balanceOutput; 

    return targets; 
} 