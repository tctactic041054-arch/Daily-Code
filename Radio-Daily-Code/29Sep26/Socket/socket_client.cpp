#include <iostream>
#include <cmath>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


int main() {
    //1. calculate for fspl
    double freq_mhz = 144.0;
    double distance_km = 10.0;
    double fspl_db = 20 * std::log10(distance_km) + 20 * std::log10(freq_mhz) + 32.44;

    //2. making socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(65432);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    //3. connect to python server
    std::cout << "[C++ CLIENT] Connecting to Python Server..." << std::endl;
    if (connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "[ERROR] Connection Failed!" << std::endl;
        return -1;
    }

    //4. prepare for data and snd by socket 
    std::string message = "FSPL: " + std::to_string(fspl_db) + " dB (Freq: " + std::to_string(freq_mhz) + "MHz)";
    send(sock, message.c_str(), message.length(), 0);
    std::cout << "[SUCCESS] Sent data to Python: " << message << std::endl;

    close(sock);
    return 0;
}