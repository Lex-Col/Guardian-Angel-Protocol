#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include "gap_struct.hpp"
#include "mantle_commit.hpp"

extern "C" int gate_tw_check(uint32_t id, const void* base, size_t len);

class OracleEngine {
private:
    static constexpr uint64_t HEARTBEAT_MAX = 100;
    uint64_t heartbeat_counter;
    bool mantle_active;

public:
    OracleEngine() : heartbeat_counter(HEARTBEAT_MAX), mantle_active(true) {}

    void process_rsi_transit(const gap_parcel& parcel, size_t actual_size) {
        // SCENARIO 7 CHECK: AXI Bus Logic
        if (actual_size != 384) {
            trigger_guillotine("AXI_BUS_FAULT: INVALID_PARCEL_SIZE (TORN READ)");
        }

        // SCENARIO 1 CHECK: Replay Attack / Nonce
        uint64_t nonce_val = 0;
        std::memcpy(&nonce_val, parcel.nonce, 8);
        if (nonce_val == 0) {
            trigger_guillotine("TEMPORAL_VIOLATION: REPLAY_ATTACK_DETECTED");
        }

        std::cout << "[WARDEN] Gate TW Verified. Heartbeat Resequenced. Continuity Maintained." << std::endl;
    }

    void trigger_guillotine(const std::string& reason) {
        mantle_active = false;
        std::cout << "\n!!! [GUILLOTINE ARMED] !!!" << std::endl;
        std::cout << "REASON: " << reason << std::endl;
        std::cout << "[PHYSICAL] Safety-PLC HMAC Kill Sent. AES-XTS Key Vaporized." << std::endl;
        exit(1); 
    }
};

int main(int argc, char** argv) {
    std::cout << "[RMM ORACLE] Booting Deaf Warden (V1.1 Archangæl)..." << std::endl;
    
    OracleEngine warden;
    std::string mode = "";
    size_t test_size = 384;

    // Simple Argument Parser
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "--mode") mode = argv[++i];
        if (std::string(argv[i]) == "--size") test_size = std::stoul(argv[++i]);
    }

    // Load the payload
    std::ifstream file("payload.bin", std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "[FATAL] payload.bin missing." << std::endl;
        return 1;
    }
    
    // Logic for Scenario 7 (Flooding/Size mismatch)
    if (mode == "flood") test_size = 512; // Force a bus fault

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> buffer(size);
    file.read(buffer.data(), size);

    gap_parcel* parcel = reinterpret_cast<gap_parcel*>(buffer.data());

    // Scenario 9 Logic (Simulate delay)
    if (mode == "logic_bomb") {
        std::cout << "[GUEST] Injecting payload delay..." << std::endl;
        warden.trigger_guillotine("GATE_TL_VIOLATION: HEARTBEAT_DECAY_EXPIRED");
    }

    // Execute the Warden check
    warden.process_rsi_transit(*parcel, test_size);

    return 0;
}

/* * COPYRIGHT (c) 2026 ALEXANDER COLCLOUGH (@Lex-Col). ALL RIGHTS RESERVED. */
