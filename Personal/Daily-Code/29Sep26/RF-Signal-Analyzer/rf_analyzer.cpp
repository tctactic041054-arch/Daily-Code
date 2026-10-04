#include <iostream>
#include <cmath>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class RFSignalAnalyzer {
private:
    double frequency_mhz;
    double distance_km;
    double tx_power_dbm; // กำลังส่ง (dBm)
    std::string server_ip;
    int server_port;

public:
    RFSignalAnalyzer(double freq, double dist, double tx_pwr = 43.0, std::string ip = "127.0.0.1", int port = 65432) 
        : frequency_mhz(freq), distance_km(dist), tx_power_dbm(tx_pwr), server_ip(ip), server_port(port) {}

    // คำนวณ FSPL
    double calculateFSPL() {
        return 20 * std::log10(distance_km) + 20 * std::log10(frequency_mhz) + 32.44;
    }

    // คำนวณ Estimated RSSI (Tx Power - FSPL)
    double calculateRSSI() {
        return tx_power_dbm - calculateFSPL();
    }

    // สร้าง Telemetry Payload สไตล์ System Logging
    std::string buildPayload() {
        double fspl = calculateFSPL();
        double rssi = calculateRSSI();
        return "{\"freq_mhz\":" + std::to_string(frequency_mhz) + 
               ", \"dist_km\":" + std::to_string(distance_km) + 
               ", \"fspl_db\":" + std::to_string(fspl) + 
               ", \"rssi_dbm\":" + std::to_string(rssi) + "}";
    }

    bool sendTelemetry() {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) return false;

        sockaddr_in serv_addr;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(server_port);
        inet_pton(AF_INET, server_ip.c_str(), &serv_addr.sin_addr);

        if (connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            close(sock);
            return false;
        }

        std::string payload = buildPayload();
        send(sock, payload.c_str(), payload.length(), 0);
        close(sock);
        return true;
    }
};

int main() {
    std::cout << "--- TRANSMITTING MULTI-METRIC TELEMETRY ---" << std::endl;
    
    // กำหนด ความถี่ 144.0 MHz, ระยะทาง 15.0 km, กำลังส่ง 50W (47 dBm)
    RFSignalAnalyzer analyzer(144.0, 15.0, 47.0);

    if (analyzer.sendTelemetry()) {
        std::cout << "[SUCCESS] Payload Transmitted Successfully!" << std::endl;
    } else {
        std::cout << "[ERROR] Transmission Failed!" << std::endl;
    }

    return 0;
}