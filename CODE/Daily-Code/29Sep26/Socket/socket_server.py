import socket
# 1. setup server
HOST = '127.0.0.1' #localhost
PORT = 65432 # Port for RF

print("--- PYTHON RF TELEMETRY SERVER ---")
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print(f"[WAITING] Listening on {HOST}:{PORT}...")
    conn, addr = s.accept()
    with conn:
        print(f"[CONNECTED] Connected by {addr}")
        data = conn.recv(1024)
        print(f"[RECEIVED DATA]: {data.decode('utf-8')}")