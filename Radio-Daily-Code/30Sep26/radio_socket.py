import struct
import serial

# [Radio Technical Specs Summary]
# 1. Packet Airtime (1200 Baud AFSK): ~473 ms for 71-byte frame
# 2. 1/4 Wave Dipole Antenna Length @ 145 MHz: ~49.1 cm per element
# 3. Validation: CRC16-CCITT used over simple checksum for robust bit-flip detection

# Packet Definition (Total: 71 Bytes)
# Format: < (Little-Endian) B (Sender) B (Receiver) H (PacketID) B (PayloadLen) 64s (Payload) H (CRC16)


import json
from datetime import datetime

def log_packet_to_json(data_dict, filename="packet_log.json"):
    data_dict["timestamp"] = datetime.now().isoformat()
    with open(filename, "a", encoding="utf-8") as f:
        f.write(json.dumps(data_dict, ensure_ascii=False) + "\n")

PACKET_SIZE = 71
STRUCT_FORMAT = '<BBHB64sH'

def calculate_crc16(data: bytes) -> int:
    """คำนวณ CRC16-CCITT (Poly: 0xA001) สำหรับตรวจสอบความถูกต้องของสัญญาณวิทยุ"""
    crc = 0xFFFF
    for byte in data:
        crc ^= byte
        for _ in range(8):
            if crc & 0x0001:
                crc = (crc >> 1) ^ 0xA001
            else:
                crc >>= 1
    return crc

def parse_radio_packet(raw_bytes: bytes):
    # 1. Byte Boundary Guard
    if len(raw_bytes) != PACKET_SIZE:
        print(f"[REJECTED] Invalid Frame Length: {len(raw_bytes)} / {PACKET_SIZE} Bytes")
        return None

    # 2. Unpack Raw Structural Bytes
    sender, receiver, packet_id, payload_len, raw_payload, received_crc = struct.unpack(STRUCT_FORMAT, raw_bytes)

    # 3. Sanity Check on Payload Length Field
    if payload_len > 64:
        print(f"[REJECTED] Corrupted Payload Length Indicator: {payload_len} (Max 64)")
        return None

    # 4. CRC16 Checksum Verification (69 Bytes Payload + Header vs 2 Bytes CRC)
    computed_crc = calculate_crc16(raw_bytes[:69])
    if computed_crc != received_crc:
        print(f"[REJECTED] Bad CRC Error. Computed: {hex(computed_crc)} | Received: {hex(received_crc)}")
        return None

    # 5. Safe Decoding
    decoded_payload = raw_payload[:payload_len].decode('utf-8', errors='ignore')

    return {
        "status": "SUCCESS",
        "sender_id": sender,
        "receiver_id": receiver,
        "packet_id": packet_id,
        "payload_len": payload_len,
        "payload": decoded_payload
    }

# --- MAIN EXECUTION LOOP ---
if __name__ == "__main__":
    print("[SYSTEM] Radio Protocol Receiver Active. Listening on Virtual Serial...")
    
    # ตัวอย่างการจำลองรับค่า Raw Bytes ขนาด 71 ไบต์
    # ในการใช้งานจริง มึงเปิด serial.Serial('/dev/pts/2', 115200) แล้ว read(71) เข้ามา
    dummy_payload = b"SYSTEM_ONLINE_EXECUTE_NOW"
    dummy_len = len(dummy_payload)
    padded_payload = dummy_payload.ljust(64, b'\x00')
    
    # ประกอบ Header + Payload เพื่อหา CRC จริง
    header_and_payload = struct.pack('<BBHB64s', 0x01, 0x02, 1001, dummy_len, padded_payload)
    valid_crc = calculate_crc16(header_and_payload)
    
    # Frame 71 Bytes สมบูรณ์
    valid_packet = header_and_payload + struct.pack('<H', valid_crc)
    

    # Execute Test
    result = parse_radio_packet(valid_packet)
    print(f"[OUTPUT] {result}")
    if result:
        log_packet_to_json(result)

