#include <iostream>
#include <fstream>
#include <vector>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include "gap_struct.hpp"
#include "whitelist.hpp"

void trigger_guillotine() {
    std::cerr << "\n[!] EXECUTING ATOMIC INHIBIT SEQUENCE..." << std::endl;
    std::ofstream bbsram("/data/data/com.termux/files/home/.gap_sim/bbsram/dirty_bit.bin", std::ios::binary);
    uint8_t dirty_flag = 0x01;
    bbsram.write(reinterpret_cast<char*>(&dirty_flag), 1);
    bbsram.close();
    
    std::ofstream rpmb("/data/data/com.termux/files/home/.gap_sim/rpmb/anomaly_log.txt", std::ios::app);
    rpmb << "[VIOLATION] Capability ID mismatch or logic error.\n";
    rpmb.close();
    std::cerr << " -> Sector isolated. Heartbeat terminated.\n" << std::endl;
}

bool constant_time_eq(uint8_t a, uint8_t b) {
    volatile uint8_t x = a ^ b;
    return x == 0;
}

int main() {
    std::cout << "[RMM ORACLE] Booting Deaf Warden..." << std::endl;

    CHA_Struct_t payload;
    std::ifstream payload_in("payload.bin", std::ios::binary);
    if (!payload_in.read(reinterpret_cast<char*>(&payload), sizeof(CHA_Struct_t))) {
        return 1;
    }

    std::ifstream sig_in("payload.sig", std::ios::binary);
    std::vector<unsigned char> signature((std::istreambuf_iterator<char>(sig_in)), std::istreambuf_iterator<char>());

    // 1. Policy check
    if (!constant_time_eq(payload.policy_zero_tolerance, 0x01)) {
        trigger_guillotine();
        return 1;
    }

    // 2. Capability ID check (Mapping payload bytes to uint16)
    uint16_t req_id = (payload.command_id[0] << 8) | payload.command_id[1];
    if (!is_authorized_capability(req_id)) {
        trigger_guillotine();
        return 1;
    }

    // 3. Cryptographic Signature check
    FILE* pub_key_file = fopen("/data/data/com.termux/files/home/.gap_sim/hsm/hsm_public.pem", "r");
    EVP_PKEY* pub_key = PEM_read_PUBKEY(pub_key_file, NULL, NULL, NULL);
    fclose(pub_key_file);

    EVP_MD_CTX* md_ctx = EVP_MD_CTX_new();
    EVP_DigestVerifyInit(md_ctx, NULL, EVP_sha384(), NULL, pub_key);
    EVP_DigestVerifyUpdate(md_ctx, &payload, sizeof(CHA_Struct_t));
    int auth_status = EVP_DigestVerifyFinal(md_ctx, signature.data(), signature.size());
    
    EVP_MD_CTX_free(md_ctx);
    EVP_PKEY_free(pub_key);

    if (auth_status != 1) {
        trigger_guillotine();
        return 1;
    }

    std::cout << "[AUTHORIZED] Triple-check passed. Realm operation permitted." << std::endl;
    return 0;
}
