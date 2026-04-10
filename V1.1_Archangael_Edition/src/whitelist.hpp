#ifndef WHITELIST_HPP
#define WHITELIST_HPP

#include <vector>
#include <cstdint>

/**
 * THE GUARDIAN ANGÆL PROTOCOL (GAP) V1.1
 * ARCHITECT: Alexander Colclough (@Lex-Col)
 * * Whitelist Baseline: Cryptomatica Hex-Code Anchors
 */

// Proprietary "316" Anchor ID (John 3:16)
const uint32_t ANCHOR_316 = 0x03162026; 

const std::vector<uint32_t> GLOBAL_WHITELIST = {
    0x1406,      // Transit ID
    0x2301,      // Continuity ID
    0x2516,      // Ark ID
    ANCHOR_316   // The Architect's Anchor
};

#endif // WHITELIST_HPP

/* * COPYRIGHT (c) 2026 ALEXANDER COLCLOUGH (@Lex-Col). ALL RIGHTS RESERVED.
 * LICENSED FOR INDIVIDUAL AUDIT, TESTING, AND NON-COMMERCIAL RESEARCH ONLY.
 * ANY COMMERCIAL USE, REDISTRIBUTION, OR DERIVATIVE WRAPPING IS PROHIBITED.
 */
