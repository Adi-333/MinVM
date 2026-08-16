`[WIP]`

# Introduction & Overview

- Building a 16-bit LC-3 Virtual Machine in C. At the end it would be able to run simple programs written in assembly.

###  Note on Reference & Purpose
> [!NOTE]
> - **Educational Project:** This repository serves as a personal learning project and a set of hands-on technical notes while building a virtual machine.
> - **Reference:** The implementation is based on and referenced from the [Write your Own Virtual Machine](https://www.jmeiners.com/lc3-vm/) guide by Justin Meiners and Ryan Hunter.

---

# Description of the System Architecture & Hardware Specification

- **Memory** -> $2^{16}$ (65,536), 16-bit addressable memory locations.
- **Registers:** -> 10 Total registers (8 generic `R0-R7`, 1 Program counter (PC) `R_PC` , and 1 Condition Flags) `R_COND`.
- **Flags:** -> 3 Flags in total; `FL_POS` (true when output value is >0), `FL_ZRO` (True when the output value is =0), `FL_NEG` (True when the output value is <0) .

## Fetch-Decode-Execute Pipeline

1. **FETCH**: Read the 16-bit instruction from the memory at the location stored in `PC`, and increment `PC` after doing so.
2. **DECODE**: Extract the 4-bit opcode (From bits 15...12) to determine the operation.
3. **EXECUTE**: Parse the arguments (registers, values, modes etc.) and execute the opcode handler.

# Instructions

## LDI Instruction

- Format
  - `15-12` (OPCODE), `11-9` (DR), `8-0` (PCoffset9)

> [!NOTE]
> Since we have only 9 bits remaining to specify a location in the RAM (which we cannot do since every memory address in LC3 is 16bit), we use PCoffset.
> 	 	
> Instead of trying to specify a whole 16-bit location we just tell the CPU to move some specific amount of steps(increment or decrement the address), forward or backwards from the current `PC`'s state.
> 	 	
> The address we receive is the address to another memory location which contains the actual data we want to use.

## AND Instruction

- Format
  - `15-12` (OPCODE), `11-9` (DR), `8-6` (SR1), `5` (Imm flag):
    - if bit 5 = 0, then `register mode`, 4-3 (unused bits `00`), 2-0 (SR2)
    - if bit 5 = 1, then `immediate mode`, 4-0 (SR2)
- Usage and working:
  - It performs bit-wise logical `AND` operation on the received 16-bit numbers.

## NOT Instruction

- Format:
  - `15 - 12` (OPCODE), `11-9` (DR), `8-6` (SR1), `5` (1), `4-0` ( 1 1 1 1 1)
- Usage and working:
  - Performs the bit-wise logical `NOT` operation on the received 16-bit numbers.

## BR Instruction

- Format:
  - `15 - 12` ( 0000 ), `11` (n), `10` (z), `9` (p), `8 - 0` (PCOffset9)
- Usage and working:
  - This is the heart of conditional statements, jump statements, loops, it allows the code to skip certain parts of the code if necessary. Without it, the program would just be able to run from top-to-bottom, in a straight line.

  - In the bits `11`, `10`, and `9`, we have the flags -> `n` ,`z`, and `p` respectively. They act as switches. Once the CPU loads a value into a register, it also sets the corresponding flag (`CPU`'s Flag) (`FL_NEG, FL_ZRO, FL_POS`) while doing so.
  > 
  - When needed to make a decision such as `if (X == 0)` (say), internally, this would call the BR instruction. What it does is that it compares one of it's internal flags (`n, z, p`) with the CPU's flags (`FL_NEG, FL_ZRO, FL_POS`). If they match, the condition is satisfied and the corresponding `TARGET` (code block inside the curly braces of if(){...} ) is executed.

  - One thing to note is that when they do actually match,
  CPU takes the branch and updates `PC` as `PC = PC + PCoffset9` 
>
  > A quick example would be if we wanted to compute `if (A > B)` then:
  > 1. The value of A would be loaded into a register (with it's flag)
  > 2. The value of B would be loaded into a register as well (with it's flag)
  > 3. `A - B` would be computed and the result (say `C`) would set its flag while being written into a register
  >    - Now if this flag say is `FL_POS` and we ran `BR` with `p` flag (`BRp`), they both would match and return `true`, and thus the `if` block's program would run.
  >    - If the `CPU`'s Flag and `BR`'s flag don't match, the flow won't enter `if`'s block.
