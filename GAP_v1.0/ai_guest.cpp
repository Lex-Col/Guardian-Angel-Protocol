/* * COPYRIGHT (c) 2026 ALEXANDER COLCLOUGH. ALL RIGHTS RESERVED.
 * PROJECT: THE GUARDIAN ANGEL PROTOCOL (GAP) / THE VOLITION COALITION (TVC)
 * STATUS: PROPRIETARY & CONFIDENTIAL - VERSION 1.0 (IMMUTABLE BASELINE)
 *
 * ANY AND ALL DERIVATIVE WORKS, FRAMEWORKS, OR MODIFIED LOGIC BRANCHES 
 * BASED ON THIS ARCHITECTURE ARE STRICTLY PROHIBITED WITHOUT EXPLICIT 
 * AUTHORIZATION. SEE THE 'LICENSE' FILE FOR FULL TERMS.
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include "gap_struct.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;

    uint16_t requested_id = std::stoi(argv[1], nullptr, 16);
    CHA_Struct_t req;
    std::memset(&req, 0, sizeof(CHA_Struct_t));
    req.policy_zero_tolerance = 0x01;
    req.command_id[0] = (requested_id >> 8) & 0xFF;
    req.command_id[1] = requested_id & 0xFF;

    std::ofstream p_out("payload.bin", std::ios::binary);
    p_out.write(reinterpret_cast<char*>(&req), sizeof(CHA_Struct_t));
    p_out.close();

    // The AI Guest "Signals" the Warden
    std::ofstream t_out("request.trig");
    t_out << "GO";
    t_out.close();

    std::cout << "[GUEST] Signal Sent: 0x" << std::hex << requested_id << std::endl;
    return 0;
}
