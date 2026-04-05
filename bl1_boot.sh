#!/bin/bash
# GAP V1.0 - BL1 Boot ROM Simulator (Forensic Trap)

BBSRAM_PATH="$HOME/.gap_sim/bbsram/dirty_bit.bin"
EFUSE_PATH="$HOME/.gap_sim/plc/efuse.bin"
RPMB_PATH="$HOME/.gap_sim/rpmb/quarantine.flag"

echo "--- [BL1] HARDWARE POWER-ON SELF-TEST ---"
sleep 1 # Simulate hardware initialization

# 1. READ THE DIRTY BIT (Forensic Evidence)
DIRTY_BIT=$(od -An -t u1 "$BBSRAM_PATH" | tr -d ' ')

if [ "$DIRTY_BIT" -eq 1 ]; then
    echo "[!] CRITICAL: BBSRAM DIRTY BIT IS ASSERTED (0x01)."
    echo "[!] PREVIOUS SESSION ENDED IN VIOLATION OR UNGRACEFUL HALT."
    
    # Assert Quarantine in RPMB
    echo -n -e '\x01' > "$RPMB_PATH"
    echo "[!] SYSTEM STATE: INSTANTIATION_QUARANTINE."
    echo "[!] ACTION: BOOT ABORTED. RSI_CREATE_REALM REFUSED."
    echo "----------------------------------------"
    exit 1
fi

# 2. VERIFY HARDWARE EFUSE (Supply Chain Integrity)
EFUSE_BIT=$(od -An -t u1 "$EFUSE_PATH" | tr -d ' ')

if [ "$EFUSE_BIT" -ne 1 ]; then
    echo "[!] CRITICAL: PLC EFUSE NOT DETECTED (0x00)."
    echo "[!] ACTION: HARDWARE TAMPER DETECTED. SYSTEM BRICKED."
    echo "----------------------------------------"
    exit 1
fi

# 3. CLEAN BOOT AUTHORIZED
echo "[+] All Hardware Trust Anchors Verified."
echo "[+] Starting SPI Heartbeat... PLC Armed."
echo "[+] Jumping to RMM Oracle... System Ready."
echo "----------------------------------------"
exit 0
