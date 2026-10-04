// main.cpp (ส่วนที่ต้องแก้ไข)
#include <iostream>
#include <cstring>
#include "mesh_packet.hpp"
#include "mesh_router.hpp"

int main() {
    MeshRouter router;

    // 1. สร้าง Packet เริ่มต้น (TTL = 3)
    MeshPacket pkt{};
    pkt.header = 0xAA;
    pkt.ttl = 3;
    pkt.sender_id = 1001;
    pkt.msg_type = 1;
    std::strncpy(pkt.payload, "Routing Test Data", sizeof(pkt.payload));
    pkt.crc16 = PacketProcessor::calculate_crc16(
        reinterpret_cast<const uint8_t*>(&pkt), 
        sizeof(MeshPacket) - sizeof(uint16_t)
    );

    // เก็บสำเนา Original Packet เอาไว้ทดสอบ Duplicate
    MeshPacket original_pkt = pkt; 

    std::cout << "[TEST 1] First Incoming Packet (TTL=3)... ";
    auto res1 = router.process_incoming_packet(pkt);
    if (res1 == MeshRouter::RouteResult::FORWARD && pkt.ttl == 2) {
        std::cout << "SUCCESS (Forwarded, New TTL=2)\n";
    } else {
        std::cout << "FAILED\n";
    }

    // 2. ส่ง Original Packet ซ้ำเข้ามา ( Duplicate Test ด้วย CRC เดิม)
    std::cout << "[TEST 2] Duplicate Packet Stream... ";
    auto res2 = router.process_incoming_packet(original_pkt);
    if (res2 == MeshRouter::RouteResult::DROP_DUPLICATE) {
        std::cout << "SUCCESS (Duplicate Dropped)\n";
    } else {
        std::cout << "FAILED\n";
    }

    // 3. ทดสอบ TTL หมดอายุ (TTL = 1)
    MeshPacket expired_pkt = pkt;
    expired_pkt.sender_id = 9999; // เปลี่ยน ID ให้ CRC ต่าง
    expired_pkt.ttl = 1;
    expired_pkt.crc16 = PacketProcessor::calculate_crc16(
        reinterpret_cast<const uint8_t*>(&expired_pkt), 
        sizeof(MeshPacket) - sizeof(uint16_t)
    );

    std::cout << "[TEST 3] Expired Packet (TTL=1)... ";
    auto res3 = router.process_incoming_packet(expired_pkt);
    if (res3 == MeshRouter::RouteResult::DROP_TTL_EXPIRED) {
        std::cout << "SUCCESS (TTL Expired Dropped)\n";
    } else {
        std::cout << "FAILED\n";
    }

    return 0;
}