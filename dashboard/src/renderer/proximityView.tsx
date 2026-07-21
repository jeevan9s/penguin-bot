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

  return (
    <div className="relative bg-[#141414] border border-[#2a2a2a] rounded flex items-center justify-center overflow-hidden">
      <div ref={mountRef} className="w-full h-full" />
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