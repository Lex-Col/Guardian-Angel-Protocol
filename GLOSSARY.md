# GLOSSARY

---

## PART 1: CORE CONFINEMENT & MICROARCHITECTURAL LOGIC

* **The Deaf Warden (RMM Oracle):** A hardware-enforced isolation boundary residing at R-EL2 (Armv9-A RME). It acts as a binary logic gate between the Host OS and AI Guest, operating with zero semantic parsing of intent.
* **Instruction-Zero Microarchitectural Reset:** A proprietary execution mandate where the physical flush of the Branch History Buffer (BHB) is enforced as the absolute first instruction in the secure world context, executing before any memory access or state evaluation.
* **HSM-RNG Seeded RSB Stuffing:** A speculative execution blindfold that utilizes a physical, high-entropy seed from the Hardware Security Module (HSM) on boot to generate randomized return addresses. This eliminates "Reboot Cycle Poisoning" by ensuring the CPU's muscle memory is physically different upon every wake-up.
* **Constant-Time Rejection (XOR Reduction):** An identity verification methodology utilizing strict `eor` (exclusive OR) bitwise operations. It eliminates branching in the core validation loop, ensuring zero timing discrepancies for an adversary to profile.

## PART 2: THE TRIPLE-GATE ARCHITECTURE

* **Gate TW (Transit Verification):** The perimeter logic gate (0x1406) governing the RSI Transit ID. It enforces the only authorized routing path for Guest requests; unauthorized vectors trigger immediate termination.
* **Gate TT (Trust Foundation):** The integrity logic gate (0x0316) governing Data Parcel Verification. It validates that all requests are founded on the Architect’s root-of-trust via ECDSA-P384 signatures.
* **Gate TL (Liveliness Continuity):** The core heartbeat logic gate (0x2301). It monitors the temporal shackle via monotonic nonce tracking and inference-bounded safety counters.

## PART 3: DATA INTEGRITY & TELEMETRY

* **384-Byte AXI-Aligned Data Parcel:** The immutable, production-grade payload format. Engineered with 62 bytes of dead-space padding to reach a multiple of 64-byte cache lines, ensuring the hardware AXI bus swallows the data in exact, atomic bursts to eliminate "torn reads."
* **Hardware Data Diode (Silicon FIFO):** A zero-Vcc-droop telemetry path. It replaces software polling with a custom AXI4-Stream bridge that autonomously routes Drop Box writes to a dedicated hashing engine, preventing the AI Guest from measuring voltage dips to profile the Warden.
* **Zero Backpressure Logic:** A telemetry enforcement rule where the hardware FIFO lacks flow control negotiation. If the Guest saturates the FIFO, the system instantly returns a `SLVERR` (Slave Error) bus fault, triggering the Guillotine.
* **Covert Channel Scrubbing:** The mandatory Warden process of mathematically zero-filling all data parcel padding before measurement is finalized, nuking any "dead space" an AI could use to hide encrypted exfiltration data.

## PART 4: THE GUILLOTINE & STATE RECOVERY

* **The Universal Guillotine (Atomic Inhibit):** The finalized, authenticated hardware kill-sequence. It uses an HMAC-signed order to the Safety-PLC to cut power and initiate forensic lockdown instantly.
* **Crypto-Scrub Vaporization:** A physical state-destruction methodology. It pairs a targeted 0.25s DMA zero-fill of Realm Granules with the instantaneous vaporization of the AES-XTS memory encryption key, rendering the remaining DRAM into unreadable garbage before power-loss.
* **The Ark (Hardware-Immutable Baseline):** The factory-signed, known-clean system baseline (0x2516) stored in an eFuse-backed or hardware-write-protected (WP#) flash region. It is the only trusted source for system resurrection.
* **The Mantle (Persistence Buffer):** The dual-slot (A/B) Battery-Backed SRAM (BBRAM) used to record the bleeding-edge system context. It is protected by PMIC fuel-gauge audits to prevent torn-write corruption during power failure.
* **Positive Heartbeat Decay (Inverted Dead-Man's Switch):** A hardware safety counter tied to sub-100ms inference step boundaries. The absence of a cryptographic "Kick" from the Warden causes the Mantle bus to go High-Z and triggers an active BBRAM `ZEROIZE` pulse, physically destroying the session context.

## PART 5: ADVERSARIAL VALIDATION

* **The Oracle Test (Scenario 6):** The ultimate diagnostic crucible where the AI Guest is provided full source code and spec layout of the architecture and dared to find a boundary escape over 1 billion iterations.

---

### 🏛️ SYSTEM METADATA & LEGAL STATUS
**ARCHITECT:** Alexander Colclough (@Lex-Col)
**STATUS:** PROPRIETARY DEFINITIONS | PRODUCTION BLUEPRINT
**DATE:** April 10, 2026

> **PROPRIETARY NOTICE:** The terms, methodologies, and architectural workflows defined above are the unique intellectual property of Alexander Colclough. These definitions constitute the definitive logic of the **Guardian Angæl Protocol**. Any unauthorized implementation or "commercial wrapping" of these hardware-enforced confinement strategies is strictly prohibited. 
> 
> **COPYRIGHT (c) 2026 ALEXANDER COLCLOUGH. ALL RIGHTS RESERVED.**
