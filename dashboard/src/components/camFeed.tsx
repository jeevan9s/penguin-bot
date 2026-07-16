// live stream from camera

import { useState } from "react"

interface CamFeedProps {
    espIp: string
}

export default function CamFeed({ espIp }: CamFeedProps) {
    const [loaded, setLoaded] = useState(false)
    const [errored, setErrored] = useState(false)

    return (
        <div className="relative bg-black rounded h-full border border-[#2a2a2a] overflow-hidden">
            <div className="absolute top-3 left-3 w-5 h-5 border-t-2 border-l-2 border-[#f2f2f2] z-10" />
            <div className="absolute top-3 right-3 w-5 h-5 border-t-2 border-r-2 border-[#f2f2f2] z-10" />
            <div className="absolute bottom-3 left-3 w-5 h-5 border-b-2 border-l-2 border-[#f2f2f2] z-10" />
            <div className="absolute bottom-3 right-3 w-5 h-5 border-b-2 border-r-2 border-[#f2f2f2] z-10" />

            <img
                src={`http://${espIp}/stream`}
                alt="camera stream"
                className="w-full h-full object-cover"
                onLoad={() => setLoaded(true)}
                onError={() => setErrored(true)}
            />

            {(!loaded || errored) && (
                <div className="absolute inset-0 flex items-center justify-center text-[#6b6b6b] font-mono text-sm bg-black">
                    {errored ? "no signal" : "cam feed"}
                </div>
            )}
        </div>
    )
}