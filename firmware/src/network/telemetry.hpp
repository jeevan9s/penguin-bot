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

/// @brief lightweight telemtry class for serializing PenguinState data into a JsonDocument to be sent over WebSocket
class Telemetry
{
public:
    /// @brief create JsonObject for each data member and log its data based on global state
    /// additionally logs timestamp
    /// @param state global state instance
    /// @param doc root memory buffer for telemetry structure
    static void serialize(const PenguinState &state, JsonDocument &doc);
};
