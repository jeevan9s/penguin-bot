"use client";

import { useEffect, useRef, useState } from "react";
import ToggleMenu from "./toggleMenu";

interface SpeedViewProps {
  RPM1: number;
  RPM2: number;
  position1: number;
  position2: number;
  running1: boolean;
  running2: boolean;
  activeView: "board" | "speed" | "proximity";
  onSelectBoard?: () => void;
  onSelectSpeed?: () => void;
  onSelectProximity?: () => void;
}

export default function speedView({
  RPM1,
  RPM2,
  position1,
  position2,
  running1,
  running2,
  activeView,
  onSelectBoard,
  onSelectSpeed,
  onSelectProximity,
}: SpeedViewProps) {
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
      <div className="absolute bottom-3 left-3 flex gap-4 font-mono text-xs text-[#888]"></div>
    </div>
  );
}