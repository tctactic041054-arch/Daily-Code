// mesh_packet.hpp
#ifndef MESH_PACKET_HPP
#define MESH_PACKET_HPP

#include <cstdint>
#include <cstddef>

#pragma pack(push, 1)
struct MeshPacket {
    uint8_t  header;        // 1 byte
    uint8_t  ttl;           // 1 byte
    uint16_t sender_id;     // 2 bytes
    uint8_t  msg_type;      // 1 byte
    char     payload[64];   // 64 bytes
    uint16_t crc16;         // 2 bytes
};                          // Total: 71 bytes
#pragma pack(pop)

static_assert(sizeof(MeshPacket) == 71, "Error: MeshPacket size must be exactly 71 bytes!");

class PacketProcessor {
public:
    static uint16_t calculate_crc16(const uint8_t* data, size_t length);
    static bool validate_packet(const MeshPacket& packet);
};

#endif // MESH_PACKET_HPP