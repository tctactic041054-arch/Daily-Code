import socket
import random
from mesh_packet import unpack_and_validate, PACKET_SIZE

UDP_IP = "127.0.0.1"
LISTEN_PORT = 8080
FORWARD_PORT = 8081

def start_simulator():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((UDP_IP, LISTEN_PORT))
    
    print(f"[NOISE SIMULATOR] Listening on port {LISTEN_PORT}...")
    print(f"[NOISE SIMULATOR] Simulating Radio Interference & Packet Loss...\n")

    while True:
        data, addr = sock.recvfrom(1024)
        if len(data) != PACKET_SIZE:
            continue

        # Random Behavior Simulation
        dice = random.random()
        
        if dice < 0.2:
            # 20% Packet Loss (Drop packet)
            print("[SIMULATOR] ❌ PACKET LOST (Simulated Radio Interference)")
        elif dice < 0.4:
            # 20% Corrupted Packet (Flip a random bit)
            corrupted_data = bytearray(data)
            corrupted_data[10] ^= 0xFF # Corrupt byte at index 10
            print("[SIMULATOR] ⚠️ PACKET CORRUPTED (Bit Flip Injected)")
            unpack_and_validate(bytes(corrupted_data))
        else:
            # 60% Normal Packet
            print("[SIMULATOR] ✅ PACKET PASSED CLEANLY")
            unpack_and_validate(data)
            
        print("-" * 40)

if __name__ == "__main__":
    start_simulator()