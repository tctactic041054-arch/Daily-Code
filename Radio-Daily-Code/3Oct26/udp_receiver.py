import socket
from mesh_packet import unpack_and_validate, PACKET_SIZE

UDP_IP = "127.0.0.1"
UDP_PORT = 8080

def start_receiver():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((UDP_IP, UDP_PORT))
    
    print(f"[PYTHON UDP SERVER] Listening on {UDP_IP}:{UDP_PORT}...")
    print(f"[PYTHON UDP SERVER] Expecting {PACKET_SIZE}-byte Mesh Packets...\n")

    try:
        while True:
            data, addr = sock.recvfrom(1024)
            print(f"=== Incoming Packet from {addr[0]}:{addr[1]} ===")
            unpack_and_validate(data)
            print("=" * 40 + "\n")
    except KeyboardInterrupt:
        print("\n[PYTHON UDP SERVER] Shutting down server gracefully.")

if __name__ == "__main__":
    start_receiver()