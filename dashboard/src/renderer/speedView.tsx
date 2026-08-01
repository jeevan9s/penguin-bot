"use client";

import ToggleMenu from "./toggleMenu";

interface SpeedViewProps {
  RPM1: number;
  RPM2: number;
  position1: number;
  position2: number;
  running1: boolean;
  running2: boolean;
  energized: boolean;
  activeView: "board" | "speed" | "proximity";
  onSelectBoard?: () => void;
  onSelectSpeed?: () => void;
  onSelectProximity?: () => void;
}

export default function SpeedView({
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
  energized
}: SpeedViewProps) {
  const radius = 54;
  const circumference = 2 * Math.PI * radius;
  
  const getStrokeDashoffset = (rpm: number) => {
    const maxRpm = 500;
    const progress = Math.min(Math.max(rpm / maxRpm, 0), 1);
    return circumference - progress * circumference;
  };

  return (
    <div className="relative bg-[#141414] border border-[#2a2a2a] rounded flex flex-col items-center justify-start overflow-hidden w-full h-full pt-16 px-6">
      <div className="absolute top-3 right-3 flex gap-4 font-mono text-xs text-[#888] z-10">
        <ToggleMenu 
          activeView={activeView} 
          onSelectBoard={onSelectBoard}
          onSelectSpeed={onSelectSpeed}
          onSelectProximity={onSelectProximity}
        />
      </div>

      <div className="flex items-center justify-center gap-16 w-full">
        <div className="flex flex-col items-center">
          <div className="relative w-36 h-36 flex items-center justify-center">
            <svg className="w-full h-full -rotate-90">
              <circle
                cx="72"
                cy="72"
                r={radius}
                stroke="#222"
                strokeWidth="8"
                fill="transparent"
              />
              <circle
                cx="72"
                cy="72"
                r={radius}
                stroke="#cc9806"
                strokeWidth="8"
                strokeDasharray={circumference}
                strokeDashoffset={getStrokeDashoffset(RPM1)}
                strokeLinecap="round"
                fill="transparent"
                className="transition-all duration-300 ease-out"
              />
            </svg>
            <div className="absolute inset-0 flex items-center justify-center">
              <span className={`w-3 h-3 rounded-full ${running1 ? "bg-[#DEA81B]" : "bg-[#5a5a5a]"}`} />
            </div>
          </div>
          <div className="mt-4 text-center font-mono">
            <div className="text-2xl font-semibold text-white">
              {Math.round(RPM1)} <span className="text-sm text-[#888] font-normal">rpm</span>
            </div>
            <div className="text-sm text-[#888] mt-1">
              L · pos {position1}
            </div>
          </div>
        </div>

        <div className="flex flex-col items-center">
          <div className="relative w-36 h-36 flex items-center justify-center">
            <svg className="w-full h-full -rotate-90">
              <circle
                cx="72"
                cy="72"
                r={radius}
                stroke="#222"
                strokeWidth="8"
                fill="transparent"
              />
              <circle
                cx="72"
                cy="72"
                r={radius}
                stroke="#cc9806"
                strokeWidth="8"
                strokeDasharray={circumference}
                strokeDashoffset={getStrokeDashoffset(RPM2)}
                strokeLinecap="round"
                fill="transparent"
                className="transition-all duration-300 ease-out"
              />
            </svg>
            <div className="absolute inset-0 flex items-center justify-center">
              <span className={`w-3 h-3 rounded-full ${running2 ? "bg-[#DEA81B]" : "bg-[#5a5a5a]"}`} />
            </div>
          </div>
          <div className="mt-4 text-center font-mono">
            <div className="text-2xl font-semibold text-white">
              {Math.round(RPM2)} <span className="text-sm text-[#888] font-normal">rpm</span>
            </div>
            <div className="text-sm text-[#888] mt-1">
              R · pos {position2}
            </div>
          </div>
        </div>
      </div>

      <div className="w-full flex-1 flex items-center justify-center pb-6">
        <div className="relative w-48 h-28 border border-[#2a2a2a] rounded-2xl bg-[#181818] flex items-center justify-center shadow-inner">
          <div
            className={`absolute -top-4 w-20 h-8 rounded-lg border border-[#2a2a2a] transition-colors duration-200 z-10 ${
              running1 ? "bg-black border-[#DEA81B]/40 shadow-sm shadow-[#DEA81B]/20" : "bg-[#222]"
            }`}
          />
          <div className="font-mono text-xs text-[#666] tracking-widest">
            PENGUIN
          </div>
          <div
            className={`absolute -bottom-4 w-20 h-8 rounded-lg border border-[#2a2a2a] transition-colors duration-200 z-10 ${
              running2 ? "bg-black border-[#DEA81B]/40 shadow-sm shadow-[#DEA81B]/20" : "bg-[#222]"
            }`}
          />
        </div>
      </div>

         <div className="absolute top-3 left-3 flex gap-4 font-mono text-xs text-[#888]">
        <p>DRIVE</p>
      </div>

    <div className="absolute bottom-3 left-3 flex gap-4 font-mono text-[#888] z-10">
                  <p className="text-[#d8d8d8] text-xs font-mono flex items-center gap-1">
            <span
              className={`w-1.5 h-1.5 rounded-full ${
                energized
                  ? "bg-[#DEA81B]"
                  : "bg-[#5a5a5a]"
              }`}
            />
            {energized ? "energized" : "disabled"}
          </p>
        
        </div>  
    </div>
  );
}