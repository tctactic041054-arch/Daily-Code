#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

int main() {
    std::string callsign;
    double frequency;

    std::cout << "Enter Callsign: ";
    std::cin >> callsign;

    std::cout << "Enter Frequency (MHz): ";
    std::cin >> frequency;

    // เช็กย่านวิทยุสมัครเล่น 2M (144.000 - 146.000 MHz)
    if (frequency >= 144.000 && frequency <= 146.000) {
        std::cout << "[SUCCESS] Valid Amateur Radio 2M Frequency!\n";
        
        // บันทึกลงไฟล์ log.txt พร้อม Timestamp
        std::ofstream logFile("log.txt", std::ios::app);
        if (logFile.is_open()) {
            std::time_t now = std::time(nullptr);
            logFile << "Callsign: " << callsign 
                    << " | Freq: " << frequency << " MHz"
                    << " | Time: " << std::ctime(&now);
            logFile.close();
            std::cout << "[LOGGED] Saved to log.txt successfully.\n";
        }
    } else {
        std::cout << "[REJECTED] Out of Amateur Radio Band!\n";
    }

    return 0;
}