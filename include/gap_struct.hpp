#ifndef GAP_STRUCT_HPP
#define GAP_STRUCT_HPP

#include <cstdint>

#pragma pack(push, 1)
typedef struct {
    uint8_t version;               
    uint8_t key_id[4];             
    uint8_t command_id[4];         
    uint8_t parameters[256];       
    uint8_t nonce[8];              
    uint8_t policy_zero_tolerance; 
    uint8_t realm_measurement[48]; 
} CHA_Struct_t;
#pragma pack(pop)

static_assert(sizeof(CHA_Struct_t) == 322, "STRUCT SIZE MISMATCH: Target 322 bytes.");

#endif
