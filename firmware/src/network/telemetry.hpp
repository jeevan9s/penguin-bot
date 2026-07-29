/**
 * @file        telemetry.hpp
 * @brief       Header for telemtry serialization.
 * @author      Jeevan Sanchez
 * @date        2026-07-15
 *
 * PENGUIN
 */

#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include "penguin_state.hpp"

class Telemetry
{
public:
    static void serialize(const PenguinState &state, JsonDocument &doc);
};
