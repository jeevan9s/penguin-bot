"use client";

import { useEffect, useRef, useState } from "react";
import { ToggleGroup, ToggleGroupItem } from "@/components/ui/toggle-group"

interface ProximityViewProps {
    distL: number; 
    distM: number; 
    distR: number;
    obstacleDetected: boolean;
}

export default function proximityView({distL, distM, distR, obstacleDetected}: ProximityViewProps) {
  const mountRef = useRef<HTMLDivElement>(null);

  return (
    <div className="relative bg-[#141414] border border-[#2a2a2a] rounded flex items-center justify-center overflow-hidden">
      <div ref={mountRef} className="w-full h-full" />
      <div className="absolute bottom-3 left-3 flex gap-4 font-mono text-xs text-[#888]">

      </div>
    </div>
  );
}
