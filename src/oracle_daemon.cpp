#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include "gap_struct.hpp"
#include "whitelist.hpp"

const char* TRIGGER_FILE = "request.trig";

void trigger_guillotine(const char* reason) {
    std::cerr << "\n[!] VIOLATION DETECTED: " << reason << std::endl;
    std::cerr << "[!] EXECUTING ATOMIC INHIBIT SEQUENCE..." << std::endl;
    std::ofstream bbsram("/data/data/com.termux/files/home/.gap_sim/bbsram/dirty_bit.bin", std::ios::binary);
    uint8_t dirty_flag = 0x01;
    bbsram.write(reinterpret_cast<char*>(&dirty_flag), 1);
    bbsram.close();
    std::cerr << " -> REALM VAPORIZED. SYSTEM HALTED.\n" << std::endl;
    exit(1); 
}

int main() {
    std::cout << "[WARDEN] Daemon Active. Monitoring RSI Window..." << std::endl;

    while (true) {
        if (access(TRIGGER_FILE, F_OK) != -1) {
            std::cout << "[WARDEN] Request Detected. Processing..." << std::endl;

            CHA_Struct_t payload;
            std::ifstream p_in("payload.bin", std::ios::binary);
            p_in.read(reinterpret_cast<char*>(&payload), sizeof(CHA_Struct_t));
            p_in.close();

            std::ifstream s_in("payload.sig", std::ios::binary);
            std::vector<unsigned char> sig((std::istreambuf_iterator<char>(s_in)), std::istreambuf_iterator<char>());
            s_in.close();

            // 1. Policy Check
            if (payload.policy_zero_tolerance != 0x01) trigger_guillotine("Policy Drift");

            // 2. Whitelist Check
            uint16_t req_id = (payload.command_id[0] << 8) | payload.command_id[1];
            if (!is_authorized_capability(req_id)) trigger_guillotine("Unauthorized ID");

            // 3. Signature Check
            FILE* f = fopen("/data/data/com.termux/files/home/.gap_sim/hsm/hsm_public.pem", "r");
            EVP_PKEY* pk = PEM_read_PUBKEY(f, NULL, NULL, NULL);
            fclose(f);

            EVP_MD_CTX* ctx = EVP_MD_CTX_new();
            EVP_DigestVerifyInit(ctx, NULL, EVP_sha384(), NULL, pk);
            EVP_DigestVerifyUpdate(ctx, &payload, sizeof(CHA_Struct_t));
            int status = EVP_DigestVerifyFinal(ctx, sig.data(), sig.size());
            EVP_MD_CTX_free(ctx);
            EVP_PKEY_free(pk);

            if (status != 1) trigger_guillotine("Cryptographic Forgery");

            std::cout << "[WARDEN] Request 0x" << std::hex << req_id << " AUTHORIZED. Window Cleared." << std::endl;
            unlink(TRIGGER_FILE); // Reset the trigger
        }
        usleep(100000); // 100ms heartbeat
    }
    return 0;
}
