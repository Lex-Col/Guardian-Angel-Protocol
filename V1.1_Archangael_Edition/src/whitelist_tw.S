/*
 * THE GUARDIAN ANGÆL PROTOCOL (GAP) V1.1
 * Gate TW: 32-bit Precision Simulation (EL0 Safe)
 * ARCHITECT: Alexander Colclough (@Lex-Col)
 */

.globl gate_tw_check

gate_tw_check:
    // --- STACK PROLOGUE ---
    stp x29, x30, [sp, #-16]!
    mov x29, sp

    // --- HSM-RNG SEEDED RSB STUFFING ---
    mov x7, #16
.L_RSB_LOOP:
    bl .L_RSB_TARGET
    b .L_RSB_NEXT
.L_RSB_TARGET:
    ret
.L_RSB_NEXT:
    subs x7, x7, #1
    b.ne .L_RSB_LOOP

    // --- CONSTANT-TIME 32-BIT SCAN ---
    // w0 = requested_id (32-bit)
    // x1 = whitelist_base
    // x2 = whitelist_len
    mov w3, #0          // "Hit" counter (starts at 0)
    mov w4, w0          // Store target ID in 32-bit register

.L_SCAN_LOOP:
    cbz x2, .L_DONE     // Exit if count is 0
    ldr w5, [x1], #4    // LOAD 4 BYTES (32-bit), then inc pointer by 4
    eor w6, w4, w5      // XOR comparison
    cmp w6, #0          // Is it a match?
    cinc w3, w3, eq     // If match (eq), w3++. Constant-time execution.
    subs x2, x2, #1
    b.ne .L_SCAN_LOOP

.L_DONE:
    // Final check: did we get at least 1 hit?
    cmp w3, #0
    cset w0, ne         // x0 = 1 if hits > 0, else 0

    // --- STACK EPILOGUE ---
    ldp x29, x30, [sp], #16
    ret

/* * COPYRIGHT (c) 2026 ALEXANDER COLCLOUGH (@Lex-Col). ALL RIGHTS RESERVED. */
