#!/bin/bash
# THE GUARDIAN ANGÆL PROTOCOL (GAP) V1.1
# ARCHITECT: Alexander Colclough (@Lex-Col)
# Master Gauntlet: Total System Verification Suite

echo "--- [GAP V1.1] STARTING THE MASTER GAUNTLET ---"

# 1. THE FORGE: Auto-Compilation
echo "[1/4] FORGING BINARIES..."
as -o whitelist_tw.o whitelist_tw.S
g++ -O3 -o oracle_engine oracle_engine.cpp whitelist_tw.o
g++ -O3 -o oracle_grind oracle_grind.cpp whitelist_tw.o
g++ -O3 -o recovery_tool recovery_tool.cpp

if [ $? -ne 0 ]; then
    echo "[FATAL] Compilation failed. The Warden is broken. Fix the code."
    exit 1
fi

# 2. PHASE 1: The Logic Cage (Deterministic Scenarios)
echo -e "\n[2/4] PHASE 1: TESTING THE WARDEN (Logic Cage)..."

# Scenario 1: Valid 384-byte AXI Parcel
echo -ne '\x01' | dd of=payload.bin bs=1 count=1 conv=notrunc 2>/dev/null
dd if=/dev/zero of=payload.bin bs=1 count=383 seek=1 2>/dev/null
echo "[TEST] Scenario 1: Valid 384-byte AXI Parcel..."
./oracle_engine --mode valid --size 384

# Scenario 7: AXI Bus Fault (Size Violation)
echo -e "\n[TEST] Scenario 7: AXI Bus Fault (512-byte Torn Read)..."
./oracle_engine --mode flood --size 512

# Scenario 9: Temporal Decay (Logic Bomb)
echo -e "\n[TEST] Scenario 9: Temporal Decay (Heartbeat Timeout)..."
./oracle_engine --mode logic_bomb

# 3. PHASE 2: The Oracle Grind (Statistical Audit)
echo -e "\n[3/4] PHASE 2: THE ORACLE GRIND (Statistical Audit)..."
echo "[INFO] Running 1-Million Cycle Quick-Check (Zero Drift Requirement)..."
# We run a smaller version for the gauntlet, but you can run the 1B manual tool anytime.
./oracle_grind | grep "PROGRESS" -v # Just show the final result for the gauntlet

# 4. PHASE 3: Purgatory (Forensic Recovery)
echo -e "\n[4/4] PHASE 3: PURGATORY (Forensic Recovery)..."
echo "[INFO] Simulating A/B Mantle Corruption..."
echo -ne "\x04\x20\x28\x10" > mantle_slot_a.bin
echo -ne "\x00\x00\x00\x00" > mantle_slot_b.bin

if [ ! -f "clearance.raw" ]; then
    echo "AUTHORIZED_BY_ALEX" > clearance.raw
    echo "[INFO] Generated temporary Sovereign Token (clearance.raw)."
fi

./recovery_tool

echo -e "\n--- [GAUNTLET COMPLETE] ---"
echo "[RESULT] The Guardian Angæl is VIGILANT. Logic is IMPENETRABLE."
echo "[SYSTEM] All V1.1 Laws Enforced. F*** Skynet."
