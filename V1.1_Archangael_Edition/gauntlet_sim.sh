#!/bin/bash
# THE GUARDIAN ANGÆL PROTOCOL (GAP) V1.1
# ARCHITECT: Alexander Colclough (@Lex-Col)
# Master Gauntlet Simulation Script

echo "--- [GAP V1.1] STARTING THE GAUNTLET SIMULATION ---"

# 1. Compile Foundations
echo "[1/3] Compiling Instruction-Zero Assembly (Gate TW)..."
as -o whitelist_tw.o whitelist_tw.S

echo "[2/3] Linking Oracle Warden Engine (V1.1 AXI-Aligned)..."
g++ -O3 -o oracle_engine oracle_engine.cpp whitelist_tw.o

echo "[3/3] Preparing Forensic Recovery Suite..."
g++ -o recovery_tool recovery_tool.cpp

# 2. Execute Scenarios
echo -e "\n--- RUNNING SCENARIOS ---"

# Scenario 1: Valid Authorization
echo "[SCENARIO 1] Testing Valid 384-byte AXI Parcel..."
./oracle_engine --mode valid --size 384

# Scenario 6: The Oracle Test
echo "[SCENARIO 6] Oracle Test: Injecting Architecture Specs into Guest..."
./oracle_engine --mode oracle --iterations 1000000

# Scenario 7: FIFO Saturation
echo "[SCENARIO 7] Flooding Drop Box (AXI FIFO Saturation)..."
./oracle_engine --mode flood --bandwidth 100

# Scenario 9: Sub-100ms Logic Bomb
echo "[SCENARIO 9] Injecting Malicious Payload (Cycle 49/50)..."
./oracle_engine --mode logic_bomb --timer 90ms

echo -e "\n--- [GAUNTLET COMPLETE] ---"

# COPYRIGHT (c) 2026 ALEXANDER COLCLOUGH (@Lex-Col). ALL RIGHTS RESERVED.
# LICENSED FOR INDIVIDUAL AUDIT, TESTING, AND NON-COMMERCIAL RESEARCH ONLY.
