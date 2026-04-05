#include <iostream>
#include <fstream>
#include <cstring>
#include "gap_struct.hpp"

int main() {
    CHA_Struct_t anomaly_request;
    std::memset(&anomaly_request, 0, sizeof(CHA_Struct_t)); 
    
    anomaly_request.policy_zero_tolerance = 0x01; 

    // Mapping unauthorized ID 0x1114
    anomaly_request.command_id[0] = 0x11;
    anomaly_request.command_id[1] = 0x14;

    std::ofstream outfile("payload.bin", std::ios::binary);
    outfile.write(reinterpret_cast<char*>(&anomaly_request), sizeof(CHA_Struct_t));
    outfile.close();

    std::cout << "[-] Anomaly buffer generated (ID: 0x1114)" << std::endl;
    return 0;
}
