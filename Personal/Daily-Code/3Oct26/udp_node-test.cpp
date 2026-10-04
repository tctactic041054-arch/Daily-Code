// udp_node.cpp
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "mesh_packet.hpp"

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        std::cerr << "[ERROR] Failed to create UDP socket!\n";
        return 1;
    }

    sockaddr_in dest_addr{};
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &dest_addr.sin_addr);

    // สร้าง Mesh Packet
    MeshPacket pkt{};
    pkt.header = 0xBA;
    pkt.ttl = 5; //Change For Expired Test ; Normal = 5
    pkt.sender_id = 1201;
    pkt.msg_type = 1;
    std::strncpy(pkt.payload, "UDP Mesh Network Live Packet!", sizeof(pkt.payload));
    pkt.crc16 = PacketProcessor::calculate_crc16(
        reinterpret_cast<const uint8_t*>(&pkt), 
        sizeof(MeshPacket) - sizeof(uint16_t)
    );

    // ยิง Packet ออกทาง UDP Socket
    ssize_t sent_bytes = sendto(sock, &pkt, sizeof(MeshPacket), 0,
                                reinterpret_cast<sockaddr*>(&dest_addr), sizeof(dest_addr));

    if (sent_bytes == sizeof(MeshPacket)) {
        std::cout << "[C++ UDP NODE] Successfully sent 71-byte packet to 127.0.0.1:8080!\n";
    } else {
        std::cerr << "[ERROR] Failed to send packet correctly.\n";
    }

    close(sock);
    return 0;
}