#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

int main() {
    double freq_mhz;
    double distance_km;
    //Dynamic input for a user
    std::cout << "Enter Frequency (MHz): ";
    std::cin >> freq_mhz;
    std::cout << "Enter Distance (KM): ";
    std::cin >> distance_km;

    double fspl_db = 20 * std::log10(distance_km) + 20 * std::log10(freq_mhz) + 32.44;

    std::cout << "--- C++ RF SIGNAL ANALYSIS ---" << std::endl;
    std::cout << "Frequency: "<< freq_mhz << " MHz" << std::endl;
    std::cout << "Distance: " << distance_km <<" km" << std::endl;
    std::cout << "Free Space Path Loss: " << std::fixed << std::setprecision(2) << fspl_db << " dB" << std::endl;

    // save in log
    std::ofstream logFile("rf_log.txt", std::ios::app);
    logFile << "FSPL: " <<fspl_db << " dB\n";
    logFile.close();
    std::cout << "[SUCCESS] Save to rf_log.txt" << std::endl;


}