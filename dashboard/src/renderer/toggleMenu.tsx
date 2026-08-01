import React from "react";
import {
  ButtonGroup,
  ButtonGroupSeparator,
} from "./components/ui/button-group";
import { Button } from "./components/ui/button";
import { Gauge, LineDotRightHorizontal, Box } from "lucide-react";

interface ToggleMenuProps {
  activeView: "speed" | "proximity" | "board";
  onSelectSpeed?: () => void;
  onSelectProximity?: () => void;
  onSelectBoard?: () => void;
}

export default function ToggleMenu({
  activeView,
  onSelectSpeed,
  onSelectProximity,
  onSelectBoard,
}: ToggleMenuProps) {
  return (
    <ButtonGroup className="inline-flex items-center rounded-2xl border border-[#2a2a2a] bg-[#141414] p-0 shadow-sm overflow-hidden">
      {activeView !== "speed" && (
        <Button
          variant="ghost"
          onClick={onSelectSpeed}
          className="rounded-l-full rounded-r-none transition-all duration-200 ease-in-out text-zinc-400 hover:bg-zinc-800 hover:cursor-pointer hover:text-white hover:scale-105 active:scale-95"
        >
          <Gauge />
        </Button>
      )}

      {activeView !== "speed" && activeView !== "proximity" && (
        <ButtonGroupSeparator orientation="horizontal" className="h-7 mt-1 bg-zinc-500" />
      )}

      {activeView !== "proximity" && (
        <Button
          variant="ghost"
          onClick={onSelectProximity}
          className={`transition-all duration-200 ease-in-out text-zinc-400 hover:bg-zinc-800 hover:cursor-pointer hover:text-white hover:scale-105 active:scale-95 ${
            activeView === "speed" ? "rounded-l-full" : ""
          } ${activeView === "board" ? "rounded-r-full" : ""}`}
        >
          <LineDotRightHorizontal />
        </Button>
      )}

      {activeView !== "proximity" && activeView !== "board" && (
        <ButtonGroupSeparator orientation="horizontal" className="h-7 mt-1 bg-zinc-500" />
      )}

      {activeView !== "board" && (
        <Button
          variant="ghost"
          onClick={onSelectBoard}
          className="rounded-r-full rounded-l-none transition-all duration-200 ease-in-out text-zinc-400 hover:bg-zinc-800 hover:cursor-pointer hover:text-white hover:scale-105 active:scale-95"
        >
          <Box />
        </Button>
      )}
    </ButtonGroup>
  );
}