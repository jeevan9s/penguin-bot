export function connectEsp(
  ip: string,
  onMessage: (data: unknown) => void,
  onStatus: (status: boolean) => void,
) {
    const ws = new WebSocket(`ws://${ip}/ws`); 

    ws.onopen = () => {
        onStatus(true); 
    }

    ws.onclose = () => {
        onStatus(false); 
    }

    ws.onerror = () => {
        onStatus(false); 
    }

    // payload
    ws.onmessage = (event) => {
        try {
            const data = JSON.parse(event.data); 
            onMessage(data); 
        } catch {
            console.warn("malformed packet"); 
        }
    }

    return ws; 
}
