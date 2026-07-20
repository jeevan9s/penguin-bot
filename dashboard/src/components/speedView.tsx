"use client";

import { useEffect, useRef, useState } from "react";
import { ToggleGroup, ToggleGroupItem } from "@/components/ui/toggle-group"

interface SpeedViewProps {
    RPM: number; 
    speed: number; 
    position: number;
    running: boolean;
}

export default function speedView({RPM, speed, position, running}: SpeedViewProps) {
  const mountRef = useRef<HTMLDivElement>(null);

  return (
    <div className="relative bg-[#141414] border border-[#2a2a2a] rounded flex items-center justify-center overflow-hidden">
      <div ref={mountRef} className="w-full h-full" />
      <div className="absolute bottom-3 left-3 flex gap-4 font-mono text-xs text-[#888]">

      </div>
    </div>
  );
}
