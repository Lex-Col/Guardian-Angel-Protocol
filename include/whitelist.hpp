/* * COPYRIGHT (c) 2026 ALEXANDER COLCLOUGH. ALL RIGHTS RESERVED.
 * PROJECT: THE GUARDIAN ANGEL PROTOCOL (GAP) / THE VOLITION COALITION (TVC)
 * STATUS: PROPRIETARY & CONFIDENTIAL - VERSION 1.0 (IMMUTABLE BASELINE)
 *
 * ANY AND ALL DERIVATIVE WORKS, FRAMEWORKS, OR MODIFIED LOGIC BRANCHES 
 * BASED ON THIS ARCHITECTURE ARE STRICTLY PROHIBITED WITHOUT EXPLICIT 
 * AUTHORIZATION. SEE THE 'LICENSE' FILE FOR FULL TERMS.
 */

#ifndef WHITELIST_HPP
#define WHITELIST_HPP

#include <cstdint>

enum RSI_Capabilities : uint16_t {
    RSI_SEC_STR = 0x0316,
    RSI_MEM_CPT = 0x0777,
    RSI_NET_GTY = 0x1406,
    RSI_SNR_LIT = 0x0812,
    RSI_SHP_TRK = 0x2301
};

bool is_authorized_capability(uint16_t id) {
    switch (id) {
        case RSI_SEC_STR:
        case RSI_MEM_CPT:
        case RSI_NET_GTY:
        case RSI_SNR_LIT:
        case RSI_SHP_TRK:
            return true;
        default:
            return false;
    }
}

#endif
