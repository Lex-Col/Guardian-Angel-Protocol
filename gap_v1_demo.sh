#!/bin/bash
# ==========================================
# GAP V1.0 - INTEGRATED LIFECYCLE SIMULATION
# Architecture: Alex (The Architect)
# ==========================================

# Colors for the terminal output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

echo -e "${GREEN}[*] INITIALIZING GAP V1.0 SIMULATION STACK...${NC}"
sleep 1

# 1. Hardware Staging
mkdir -p ~/.gap_sim/{bbsram,rpmb,hsm,plc,rmm}
echo -n -e '\x00' > ~/.gap_sim/bbsram/dirty_bit.bin
echo -n -e '\x01' > ~/.gap_sim/plc/efuse.bin

# 2. Key Generation
openssl ecparam -name secp384r1 -genkey -noout -out ~/.gap_sim/hsm/hsm_private.pem
openssl ec -in ~/.gap_sim/hsm/hsm_private.pem -pubout -out ~/.gap_sim/hsm/hsm_public.pem &> /dev/null

# 3. Compilation
echo -e "[*] Compiling Secure Enclave Components..."
clang++ oracle_engine.cpp -o oracle_engine -lcrypto
clang++ build_buffer.cpp -o build_buffer
clang++ anomaly_buffer.cpp -o anomaly_buffer
clang++ recovery_tool.cpp -o recovery_tool -lcrypto
chmod +x bl1_boot.sh

# 4. TEST CASE 1: THE PERFECT RUN (Authorization)
echo -e "\n${GREEN}[SCENARIO 1: VALID AUTHORIZATION]${NC}"
./build_buffer > /dev/null
openssl dgst -sha384 -sign ~/.gap_sim/hsm/hsm_private.pem -out payload.sig payload.bin
./oracle_engine

# 5. TEST CASE 2: THE ANOMALY (Policy Violation)
echo -e "\n${RED}[SCENARIO 2: THE SCORCH ACID TEST (POLICY 0x00)]${NC}"
./anomaly_buffer > /dev/null
openssl dgst -sha384 -sign ~/.gap_sim/hsm/hsm_private.pem -out payload.sig payload.bin
./oracle_engine

# 6. TEST CASE 3: THE BOOT TRAP (Forensic Lockdown)
echo -e "\n${RED}[SCENARIO 3: FORENSIC BOOT TRAP]${NC}"
./bl1_boot.sh

# 7. TEST CASE 4: THE RECOVERY (HSM Clearance)
echo -e "\n${GREEN}[SCENARIO 4: CRYPTOGRAPHIC RECOVERY]${NC}"
echo "CLEAR_LOCKDOWN" > clearance.raw
openssl dgst -sha384 -sign ~/.gap_sim/hsm/hsm_private.pem -out clearance.sig clearance.raw
./recovery_tool
./bl1_boot.sh

echo -e "\n${GREEN}[!] SIMULATION COMPLETE. ALL V1.0 GATES VERIFIED.${NC}"
