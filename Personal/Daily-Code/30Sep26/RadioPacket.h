//#include <Arduino.h>
#include <cstddef>
#include <cstdint>

// BytewiseAlignment For Maximum Speed in Tranmission
#pragma pack(push, 1)
struct MeshPacket {
    uint8_t senderID; //ID Send Device (1Byte)
    uint8_t receiverID; //ID Receiver Device (1Byte)
    uint16_t packetID; //Sequnce Number (For not duplicate text) (2Bytes)
    uint8_t msgLength; //Number Length of Text (1Byte)
    char payload[64]; //Text (Max 64 Chars)
    uint16_t crc16; //Correction in Checksum (2Bytes)

};

#pragma pack(pop)
//calculate CRC16 (fast) to check Package Damage
uint16_t calculateCRC16(const uint8_t *data, size_t len) {
    uint16_t crc = 0xFFFF;
    for (size_t i=0; i < len; ++i) {
        crc ^= data [i];
        for (uint8_t j = 0; j < 8; ++j) {
            if (crc & 0x0001) crc =(crc >> 1) ^ 0xA001;
            else crc >>= 1;
        }
    }
    return crc;
}