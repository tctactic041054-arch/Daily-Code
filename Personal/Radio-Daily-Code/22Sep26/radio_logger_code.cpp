#include <iostream>
#include <fstream>


struct FrequencyLog {
    double frequency_MHz;
    double power_watts;
    int rst_signal;
};

bool validateFrequency(double freq) {
    // Validate VHF 2-Meter Band
    return (freq >= 144.000 && freq <= 148.000);
}

int main() {
    FrequencyLog log;
    
    std::cout << "=== AMATEUR RADIO LOGGING SYSTEM ===\n";
    std::cout << "Enter Frequency (MHz) [144.0 - 148.0]: ";
    std::cin >> log.frequency_MHz;

    if (!validateFrequency(log.frequency_MHz)) {
        std::cerr << "[ERROR] Frequency out of VHF 2m Amateur Band!\n";
        return 1;
    }

    std::cout << "Enter Power Output (Watts): ";
    std::cin >> log.power_watts;
    
    std::cout << "Enter Signal Report (RST e.g. 599): ";
    std::cin >> log.rst_signal;

    // File I/O Execution
    std::ofstream outFile("radio_log.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << "FREQ: " << log.frequency_MHz << " MHz | "
                << "PWR: " << log.power_watts << " W | "
                << "RST: " << log.rst_signal << "\n";
        outFile.close();
        std::cout << "[SUCCESS] Log saved to radio_log.txt\n";
    } else {
        std::cerr << "[ERROR] Unable to open log file!\n";
        return 1;
    }

    return 0;
}