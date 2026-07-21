"use client";

import { useRef } from "react";
import ToggleMenu from "./toggleMenu";

interface ProximityViewProps {
  distL: number;
  distM: number;
  distR: number;
  obstacleDetected: boolean;
  activeView: "board" | "speed" | "proximity";
  onSelectBoard?: () => void;
  onSelectSpeed?: () => void;
  onSelectProximity?: () => void;
}

const CX = 220;
const CY = 165;
const RADIUS = 150;

// Solid amber, with per-segment opacity representing closeness.
// A separate, distinct grey is used specifically for "no data" —
// readings at/beyond max range or otherwise invalid — rather than
// letting the normal far-distance fade blend into grey on its own.
const AMBER = "#DEA81B";
const NO_DATA_GREY = "#3a3a3a";
const DANGER = "#ff4d4d";

// closeness: 1 at 0cm (touching), down toward a low floor as distance
// approaches maxRange (still visibly amber, not grey — grey is reserved
// for genuine no-data readings, handled separately below).
function closeness(cm: number, maxRange: number): number {
  const clamped = Math.min(Math.max(cm, 0), maxRange);
  return 1 - clamped / maxRange;
}

function opacityForCloseness(t: number): number {
  const minOpacity = 0.18;
  const maxOpacity = 0.95;
  return minOpacity + (maxOpacity - minOpacity) * t;
}

// A reading counts as "no data" if it's invalid (<=0, a common sensor
// error/no-target sentinel) or at/beyond the sensor's max usable range.
function hasNoData(cm: number, maxRange: number): boolean {
  return cm <= 0 || cm >= maxRange;
}

// theta measured from 0 (left) to 180 (right), sweeping through "up".
function polar(theta: number, r: number) {
  const rad = (theta * Math.PI) / 180;
  return {
    x: CX - r * Math.cos(rad),
    y: CY - r * Math.sin(rad),
  };
}

function wedgePath(theta0: number, theta1: number, r: number): string {
  const start = polar(theta0, r);
  const end = polar(theta1, r);
  return `M${CX},${CY} L${start.x},${start.y} A${r},${r} 0 0,1 ${end.x},${end.y} Z`;
}

// Unequal sector widths to match the reference: a narrow center spike
// flanked by two wider side wedges, swept across ~110° (not a full 180°)
// so the base edges angle steeply up from a single bottom vertex instead
// of forming a flat-bottomed dome.
const SECTORS = [
  { key: "left", theta0: 35, theta1: 80 },
  { key: "mid", theta0: 80, theta1: 100 },
  { key: "right", theta0: 100, theta1: 145 },
] as const;

export default function ProximityView({
  distL,
  distM,
  distR,
  obstacleDetected,
  activeView,
  onSelectBoard,
  onSelectSpeed,
  onSelectProximity,
}: ProximityViewProps) {
  const mountRef = useRef<HTMLDivElement>(null);

  const readings: Record<string, number> = {
    left: distL,
    mid: distM,
    right: distR,
  };

  return (
    <div className="relative bg-[#141414] border border-[#2a2a2a] rounded flex items-center justify-center overflow-hidden">
      <div ref={mountRef} className="w-full h-full flex items-center justify-between px-6">
        <svg
          width="85%"
          height="auto"
          viewBox="0 0 440 175"
          role="img"
          aria-label={`Proximity: left ${distL.toFixed(0)}cm, mid ${distM.toFixed(0)}cm, right ${distR.toFixed(0)}cm`}
        >
          {SECTORS.map((sector) => {
            const cm = readings[sector.key];
            const maxRange = 80;
            const noData = hasNoData(cm, maxRange);
            const danger = obstacleDetected && cm > 0 && cm < 15;

            const fill = noData ? NO_DATA_GREY : danger ? DANGER : AMBER;
            const opacity = noData ? 0.4 : opacityForCloseness(closeness(cm, maxRange));

            return (
              <path
                key={sector.key}
                d={wedgePath(sector.theta0, sector.theta1, RADIUS)}
                fill={fill}
                opacity={opacity}
                style={{ transition: "fill 150ms linear, opacity 150ms linear" }}
              />
            );
          })}
        </svg>

        <div className="flex flex-col gap-3 font-mono text-xs text-[#f2f2f2]">
          <div>
            <span className="text-[#6b6b6b] block text-[10px]">LEFT</span>
            {distL.toFixed(0)}cm
          </div>
          <div>
            <span className="text-[#6b6b6b] block text-[10px]">MID</span>
            {distM.toFixed(0)}cm
          </div>
          <div>
            <span className="text-[#6b6b6b] block text-[10px]">RIGHT</span>
            {distR.toFixed(0)}cm
          </div>
        </div>
      </div>

            <div className="absolute top-3 left-3 flex gap-4 font-mono text-xs text-[#888]">
        <p>PROXIMITY</p>
      </div>

      <div className="absolute top-3 right-3 flex gap-4 font-mono text-xs text-[#888]">
        <ToggleMenu
          activeView={activeView}
          onSelectBoard={onSelectBoard}
          onSelectSpeed={onSelectSpeed}
          onSelectProximity={onSelectProximity}
        />
      </div>
    </div>
  );
}