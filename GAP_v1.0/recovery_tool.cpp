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
#include <vector>
#include <openssl/evp.h>
#include <openssl/pem.h>

int main() {
    std::cout << "[RECOVERY] Initializing Clearance Sequence..." << std::endl;

    // 1. Load the Public Key
    FILE* pub_key_file = fopen("/data/data/com.termux/files/home/.gap_sim/hsm/hsm_public.pem", "r");
    EVP_PKEY* pub_key = PEM_read_PUBKEY(pub_key_file, NULL, NULL, NULL);
    fclose(pub_key_file);

    // 2. Load the Raw Command and Signature
    std::ifstream cmd_in("clearance.raw", std::ios::binary);
    std::vector<char> command((std::istreambuf_iterator<char>(cmd_in)), std::istreambuf_iterator<char>());
    
    std::ifstream sig_in("clearance.sig", std::ios::binary);
    std::vector<unsigned char> signature((std::istreambuf_iterator<char>(sig_in)), std::istreambuf_iterator<char>());

    // 3. Verify Signature
    EVP_MD_CTX* md_ctx = EVP_MD_CTX_new();
    EVP_DigestVerifyInit(md_ctx, NULL, EVP_sha384(), NULL, pub_key);
    EVP_DigestVerifyUpdate(md_ctx, command.data(), command.size());
    int auth_status = EVP_DigestVerifyFinal(md_ctx, signature.data(), signature.size());

    if (auth_status == 1) {
        std::cout << "[SUCCESS] Clearance Token Verified. Wiping Hardware Flags..." << std::endl;
        
        // PHYSICAL WIPE: Reset BBSRAM to 0x00
        std::ofstream bbsram("/data/data/com.termux/files/home/.gap_sim/bbsram/dirty_bit.bin", std::ios::binary);
        uint8_t clean_flag = 0x00;
        bbsram.write(reinterpret_cast<char*>(&clean_flag), 1);
        bbsram.close();

        // Remove Quarantine Flag
        remove("/data/data/com.termux/files/home/.gap_sim/rpmb/quarantine.flag");
        
        std::cout << "[+] System Cleared. Ready for Standard Boot." << std::endl;
    } else {
        std::cerr << "[FAILURE] Invalid Clearance Token. Quarantine Maintained." << std::endl;
    }

    EVP_MD_CTX_free(md_ctx);
    EVP_PKEY_free(pub_key);
    return 0;
}
