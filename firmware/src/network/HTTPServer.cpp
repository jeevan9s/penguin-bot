/**
 * @file        HTTPServer.cpp
 * @brief       HTTP router.
 * @author      Jeevan Sanchez
 * @date        2026-07-15
 *
 * PENGUIN
 */

#include <Arduino.h>
#include "HTTPServer.hpp"

HTTPServer::HTTPServer(CAMDriver& cam) 
    : server(80), 
      websocket(server), 
      camera_(cam), 
      cameraStream(server, cam) 
{
}

void HTTPServer::begin() { 
  server.on("/", WebRequestMethod::HTTP_GET, [](AsyncWebServerRequest *request) { 
    request->send(200, "text/plain", "penguin --online"); 
  }); 
  
  websocket.begin(); 
  server.begin(); 
}

void HTTPServer::update(PenguinState &state) {
    websocket.update(state);
}

