// general card

export default function Card ({ label, value }: { label: string; value: string }) {
    return (
        <div className="bg-[#141414] border border-[#2a2a2a] rounded-sm p-4">
            <div className="text-[#6b6b6b] text-xs uppercase">{label}</div>
            <div className="text-[#f2f2f2] font-mono text-2xl mt-1">{value}</div>
        </div>
    )
}