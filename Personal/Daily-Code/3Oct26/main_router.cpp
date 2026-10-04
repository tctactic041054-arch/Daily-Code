#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "mesh_packet.hpp"
#include "mesh_router.hpp"

#define LISTEN_PORT 8080
#define BUFFER_SIZE 1024

int main() {
    MeshRouter router;
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // 1. Create Socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cerr << "[ERROR] Socket creation failed!" << std::endl;
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(LISTEN_PORT);

    // 2. Bind Socket
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "[ERROR] Socket bind failed!" << std::endl;
        close(sockfd);
        return 1;
    }

    std::cout << "[C++ ROUTER ENGINE] Node active and listening on port " << LISTEN_PORT << "..." << std::endl;

    // 3. Main Receive Loop & Routing Logic
    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytes_received = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
                                          (struct sockaddr *)&client_addr, &addr_len);

        if (bytes_received < 0) {
            std::cerr << "[ERROR] Failed to receive data!" << std::endl;
            continue;
        }

        // ตรวจสอบขนาดของ Packet ว่าถูกต้องตามโครงสร้าง 71 บายต์หรือไม่
        if (bytes_received == sizeof(MeshPacket)) {
            MeshPacket packet;
            memcpy(&packet, buffer, sizeof(MeshPacket));

            std::cout << "\n----------------------------------------" << std::endl;
            std::cout << "[INCOMING PACKET] Received " << bytes_received << " bytes." << std::endl;

            // รับค่าเป็น MeshRouter::RouteResult ตามที่เขียนไว้ใน header
            MeshRouter::RouteResult result = router.process_incoming_packet(packet);

            if (result == MeshRouter::RouteResult::FORWARD) {
                std::cout << "[ROUTER LOGIC] Packet Accepted & Processed Successfully!" << std::endl;
            } else if (result == MeshRouter::RouteResult::DROP_DUPLICATE) {
                std::cout << "[ROUTER LOGIC] Packet Dropped: Duplicate detected via CRC cache." << std::endl;
            } else if (result == MeshRouter::RouteResult::DROP_TTL_EXPIRED) {
                std::cout << "[ROUTER LOGIC] Packet Dropped: TTL expired (TTL == 0)." << std::endl;
            } else if (result == MeshRouter::RouteResult::DROP_CORRUPTED) {
                std::cout << "[ROUTER LOGIC] Packet Dropped: CRC Checksum Validation Failed!" << std::endl;
            }
        } else {
            std::cout << "[WARNING] Invalid packet size: " << bytes_received << " bytes" << std::endl;
        }
    }

    close(sockfd);
    return 0;
}