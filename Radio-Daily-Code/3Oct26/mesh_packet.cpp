// mesh_packet.cpp
#include "mesh_packet.hpp"
#include <cstring>

// CRC16-CCITT implementation (Polynomial: 0x1021, Init: 0xFFFF)
uint16_t PacketProcessor::calculate_crc16(const uint8_t* data, size_t length) {
    uint16_t crc = 0xFFFF;
    for (size_t i = 0; i < length; ++i) {
        crc ^= (static_cast<uint16_t>(data[i]) << 8);
        for (uint8_t bit = 0; bit < 8; ++bit) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ 0x1021;
            } else {
                crc = crc << 1;
            }
        }
    }
    return crc;
}

bool PacketProcessor::validate_packet(const MeshPacket& packet) {
    // คำนวณ CRC16 จากข้อมูลทั้งหมด ยกเว้น field crc16 สองไบต์สุดท้าย (69 ไบต์แรก)
    uint16_t computed_crc = calculate_crc16(
        reinterpret_cast<const uint8_t*>(&packet), 
        sizeof(MeshPacket) - sizeof(uint16_t)
    );
    
    return computed_crc == packet.crc16;
}