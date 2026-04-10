#ifndef GAP_STRUCT_HPP
#define GAP_STRUCT_HPP

#include <cstdint>

/**
 * THE GUARDIAN ANGÆL PROTOCOL (GAP) V1.1
 * ARCHITECT: Alexander Colclough (@Lex-Col)
 * * Master Data Parcel - AXI-Aligned (384 Bytes)
 * Ensures atomic bus bursts across ARMv9-A Confidential Compute interconnects.
 */

struct __attribute__((packed)) gap_parcel {
    uint8_t nonce[8];              // Offset 0: Monotonic counter
    uint8_t key_id[4];             // Offset 8: HSM Key Identifier
    uint8_t command_id[4];         // Offset 12: Capability Transit ID
    uint8_t parameters[256];       // Offset 16: Payload Data
    uint8_t realm_measurement[48]; // Offset 272: Runtime hash (SHA3-384)
    uint8_t version;               // Offset 320: Protocol Version (0x11)
    uint8_t policy_zero_tolerance; // Offset 321: Logic Enforcement Bit
    uint8_t _padding[62];          // Offset 322: AXI-Alignment Dead Space (Zero-filled)
};

#endif // GAP_STRUCT_HPP

/* * COPYRIGHT (c) 2026 ALEXANDER COLCLOUGH (@Lex-Col). ALL RIGHTS RESERVED.
 * LICENSED FOR INDIVIDUAL AUDIT, TESTING, AND NON-COMMERCIAL RESEARCH ONLY.
 * ANY COMMERCIAL USE, REDISTRIBUTION, OR DERIVATIVE WRAPPING IS PROHIBITED.
 */
