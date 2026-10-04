// mesh_router.hpp
#ifndef MESH_ROUTER_HPP
#define MESH_ROUTER_HPP

#include <unordered_set>
#include "mesh_packet.hpp"

class MeshRouter {
private:
    std::unordered_set<uint16_t> processed_crc_cache; // กัน Packet ซ้ำ

public:
    enum class RouteResult {
        FORWARD,
        DROP_TTL_EXPIRED,
        DROP_DUPLICATE,
        DROP_CORRUPTED
    };

    RouteResult process_incoming_packet(MeshPacket& packet) {
        // 1. Validate CRC16
        if (!PacketProcessor::validate_packet(packet)) {
            return RouteResult::DROP_CORRUPTED;
        }

        // 2. Check Duplication
        if (processed_crc_cache.count(packet.crc16) > 0) {
            return RouteResult::DROP_DUPLICATE;
        }

        // Record CRC to Cache
        processed_crc_cache.insert(packet.crc16);

        // 3. TTL Decrement Check
        if (packet.ttl <= 1) {
            return RouteResult::DROP_TTL_EXPIRED;
        }

        // Decrement TTL & Recalculate CRC16
        packet.ttl--;
        packet.crc16 = PacketProcessor::calculate_crc16(
            reinterpret_cast<const uint8_t*>(&packet),
            sizeof(MeshPacket) - sizeof(uint16_t)
        );

        return RouteResult::FORWARD;
    }
};

#endif // MESH_ROUTER_HPP