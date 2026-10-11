import socket
# initialize socket for digital radio / network control

# 1. Create Socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print("[+] Socket Created Successfully")

#2. Bind IP & Port (localhost)
HOST = '127.0.0.1'
PORT = 8080
s.bind((HOST,PORT))
print(f"[+] Bound to {HOST}:{PORT}")

#3. Listen for connections
s.listen(1)
print("[+] Server is listening...")
