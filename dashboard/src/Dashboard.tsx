"use client";

import { useState, useEffect } from "react";
import Card from "./renderer/card";
import CamFeed from "./renderer/camFeed";
import Board3D from "./renderer/board3D";
import SpeedView from "./renderer/speedView";
import ProximityView from "./renderer/proximityView";
import { connectEsp } from "./services/connect";
import parsePenguinData from "./services/fetchData";
import {
  DEFAULT_ESP_IP,
  DEFAULT_PENGUIN_DATA,
  type PenguinData,
} from "./types";

export default function Dashboard() {
  const [espIp] = useState(
    new URLSearchParams(window.location.search).get("esp") ?? DEFAULT_ESP_IP
  );

  const [connected, setConnected] = useState(false);
  const [penguinData, setPenguinData] =
    useState<PenguinData>(DEFAULT_PENGUIN_DATA);

  const [activeView, setActiveView] = useState<"board" | "speed" | "proximity">("board");

  useEffect(() => {
    const ws = connectEsp(
      espIp,
      (packet) => setPenguinData(parsePenguinData(packet)),
      setConnected
    );

    return () => ws.close();
  }, [espIp]);

  return (
    <div className="w-screen h-screen overflow-hidden bg-[#0a0a0a] flex flex-col p-12">
      <div className="flex flex-row justify-between items-center mb-4">
        <p className="text-[#f2f2f2] font-medium text-lg tracking-wider">
          penguin
        </p>

        <div className="flex flex-row items-center gap-4">
          <p className="text-[#d8d8d8] text-sm font-mono flex items-center gap-1">
            <span
              className={`w-1.5 h-1.5 rounded-full ${
                penguinData.battery.connected
                  ? "bg-[#DEA81B]"
                  : "bg-[#5a5a5a]"
              }`}
            />
            battery:{" "}
            {penguinData.battery.connected ? `connected | ${penguinData.battery.SOC}` : "disconnected"}
          </p>

          <p className="text-[#d8d8d8] text-sm font-mono flex items-center gap-1">
            <span
              className={`w-1.5 h-1.5 rounded-full ${
                connected ? "bg-[#DEA81B]" : "bg-[#5a5a5a]"
              }`}
            />
            {connected ? "online" : "offline"}
          </p>
        </div>
      </div>

      <div className="grid grid-cols-[1.6fr_1fr] gap-4 flex-1 min-h-0">
        <CamFeed espIp={espIp} />

        {activeView === "board" && (
          <Board3D
            pitch={penguinData.imu.angles.pitch}
            roll={penguinData.imu.angles.roll}
            yaw={penguinData.imu.angles.yaw}
            activeView={activeView}
            onSelectBoard={() => setActiveView("board")}
            onSelectSpeed={() => setActiveView("speed")}
            onSelectProximity={() => setActiveView("proximity")}
          />
        )}

        {activeView === "speed" && (
          <SpeedView
            RPM1={penguinData.motorL.RPM}
            RPM2={penguinData.motorR.RPM}
            position1={penguinData.motorL.position}
            position2={penguinData.motorR.position}
            running1={penguinData.motorL.running}
            running2={penguinData.motorR.running}
            energized={penguinData.battery.connected}

            activeView={activeView}
            onSelectBoard={() => setActiveView("board")}
            onSelectSpeed={() => setActiveView("speed")}
            onSelectProximity={() => setActiveView("proximity")}
          />
        )}

        {activeView === "proximity"  && (
          <ProximityView
            distL={penguinData.sensL.proximity}
            distM={penguinData.sensM.proximity}
            distR={penguinData.sensR.proximity}
            obstacleDetected={penguinData.obsDetected}
            activeView={activeView}
            onSelectBoard={() => setActiveView("board")}
            onSelectSpeed={() => setActiveView("speed")}
            onSelectProximity={() => setActiveView("proximity")}
          />
        )}
      </div>

      <div className="grid grid-cols-4 gap-4 mt-4">
        <Card
          label="X Acceleration"
          value={`${penguinData.imu.accX.toFixed(3)} g`}
        />
        <Card
          label="Y Acceleration"
          value={`${penguinData.imu.accY.toFixed(3)} g`}
        />
        <Card
          label="Z Acceleration"
          value={`${penguinData.imu.accZ.toFixed(3)} g`}
        />
        <Card
          label="Temperature"
          value={`${penguinData.imu.temp.toFixed(1)}°C`}
        />
      </div>
    </div>
  );
}