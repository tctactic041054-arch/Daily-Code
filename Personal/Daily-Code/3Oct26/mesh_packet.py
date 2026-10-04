import struct

# Structure format: uint8, uint8, uint16, uint8, 64s, uint16
# < = Little-endian, B = uint8 (1 byte), H = uint16 (2 bytes), 64s = char[64]
PACKET_FORMAT = "<BBHB64sH"
PACKET_SIZE = struct.calcsize(PACKET_FORMAT)

def calculate_crc16(data: bytes) -> int:
    crc = 0xFFFF
    for byte in data:
        crc ^= (byte << 8)
        for _ in range(8):
            if crc & 0x8000:
                crc = ((crc << 1) ^ 0x1021) & 0xFFFF
            else:
                crc = (crc << 1) & 0xFFFF
    return crc

def unpack_and_validate(raw_bytes: bytes):
    if len(raw_bytes) != PACKET_SIZE:
        print(f"[ERROR] Invalid Packet Size: {len(raw_bytes)} bytes (Expected {PACKET_SIZE})")
        return False

    header, ttl, sender_id, msg_type, payload, received_crc = struct.unpack(PACKET_FORMAT, raw_bytes)
    
    # Calculate CRC from first 69 bytes
    computed_crc = calculate_crc16(raw_bytes[:-2])
    
    is_valid = (computed_crc == received_crc)
    
    print(f"[PYTHON CHECK] Packet Size: {len(raw_bytes)} bytes")
    print(f"[PYTHON CHECK] Sender ID: {sender_id}, TTL: {ttl}")
    print(f"[PYTHON CHECK] Payload: {payload.decode('utf-8', errors='ignore').rstrip('#00')}")
    print(f"[PYTHON CHECK] Computed CRC: {hex(computed_crc)} | Received CRC: {hex(received_crc)}")
    print(f"[RESULT] Validation Status: {'SUCCESS' if is_valid else 'FAILED'}")
    
    return is_valid

if __name__ == "__main__":
    print(f"Python Mesh Packet Module Ready. Expected Struct Size: {PACKET_SIZE} bytes.")
    
    try:
        with open("packet.bin", "rb") as f:
            raw_data = f.read()
            print("\n[PYTHON BRIDGE] Reading packet.bin...")
            unpack_and_validate(raw_data)
    except FileNotFoundError:
        print("[PYTHON BRIDGE] packet.bin not found. Run C++ generator first!")