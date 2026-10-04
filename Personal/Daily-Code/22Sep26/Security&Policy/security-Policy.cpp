#include <iostream>
#include <string>

#include <memory>      // สำหรับ std::unique_ptr / std::make_uniquev


enum class SecurityLevel { BASIC, RECOMMEND, STRICT };

// Struct สำหรับ Checklist Danger ในกระดาษรูปที่ 1
struct DangerChecklist {
    bool blockNSFW = true;
    bool blockPornAndLeakedMedia = true;
    bool logPhysicalHurt = true;
    bool logLawViolations = true;
    bool monitorEmotionalStatus = false;
};

// Struct สำหรับ Sandbox & Firewall Settings
struct FirewallPolicy {
    bool checkIncoming = true;
    bool checkOutcoming = true;
};

class SecurityEngine {
private:
    SecurityLevel currentLevel;
    DangerChecklist dangerRules;
    FirewallPolicy firewall;
    int securityScore;

public:
    SecurityEngine(SecurityLevel level) : currentLevel(level), securityScore(100) {
        applyPolicyByLevel();
    }

    void applyPolicyByLevel() {
        if (currentLevel == SecurityLevel::STRICT) {
            dangerRules.monitorEmotionalStatus = true;
            std::cout << "[POLICY] STRICT Level Applied: VM Isolation & Strict Firewall Active.\n";
        } else if (currentLevel == SecurityLevel::RECOMMEND) {
            std::cout << "[POLICY] RECOMMEND Level Applied: Basic + Emotional Status Monitor.\n";
        } else {
            std::cout << "[POLICY] BASIC Level Applied.\n";
        }
    }

    bool inspectPacket(const std::string& packetData, bool isIncoming) {
        std::cout << "[FIREWALL] Inspecting " << (isIncoming ? "Incoming" : "Outcoming") << " packet...\n";
        // Logic ตรวจสอบ Packet
        if (packetData.find("MALWARE") != std::string::npos || packetData.find("NSFW") != std::string::npos) {
            std::cout << "[ALERT] Threat Detected! Packet Blocked.\n";
            securityScore -= 10;
            return false;
        }
        return true;
    }

    void displayStatus() const {
        std::cout << "\n====================================\n";
        std::cout << " SYSTEM SECURITY SCORE: " << securityScore << "/100\n";
        std::cout << " Firewall Incoming Check: " << (firewall.checkIncoming ? "ON" : "OFF") << "\n";
        std::cout << " Firewall Outcoming Check: " << (firewall.checkOutcoming ? "ON" : "OFF") << "\n";
        std::cout << "====================================\n";
    }
};



enum class GroupType { SUDO, ROOT, VPN, VM, SANDBOX }; // เปลี่ยนชื่อ Enum ไม่ให้ซ้ำกับ class

class GroupManager {
private:
    GroupType type;
    std::string description;

public:
    GroupManager(GroupType t) : type(t) {
        if (type == GroupType::SUDO) {
            description = "This is a group that can be used to access root temporarily.";
        } else if (type == GroupType::ROOT) {
            description = "This is a group that can be used to access root permanently.";
        }
    }

    void displayInfo() const {
        std::cout << "[GROUP LOG] " << description << "\n";
    }
};

class VPNManager {
private:
    std::string vpnName;
    bool isCertificateValid;

public:
    VPNManager(const std::string& name, bool certStatus) 
        : vpnName(name), isCertificateValid(certStatus) {}

    bool verifyAndInstall() const {
        std::cout << "[VPN] Checking Certificate for " << vpnName << "...\n";
        if (!isCertificateValid) {
            std::cout << "[ALERT] Invalid Certificate! VPN Installation Blocked.\n";
            return false;
        }
        std::cout << "[VPN] Certificate Validated. Access Granted for Installation.\n";
        return true;
    }
};

int main() {
    std::cout << "=== TCOS / SECURITY POLICY ENGINE SIMULATOR ===\n\n";
    
    // สร้าง Smart Pointer ด้วย std::make_unique
    auto engine = std::make_unique<SecurityEngine>(SecurityLevel::STRICT);
    
    // เวลาเรียกใช้ Method ให้ใช้เครื่องหมาย ->
    engine->inspectPacket("GET /normal_data HTTP/1.1", true);
    engine->inspectPacket("POST /upload_NSFW_file HTTP/1.1", true);
    engine->displayStatus();

    return 0;
}