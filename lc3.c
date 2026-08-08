#include <stdio.h>
#include <stdint.h>

#define MAX_MEMORY (1 << 16)


enum{
  R_R0 = 0,
  R_R1,
  R_R2,
  R_R3,
  R_R4,
  R_R5,
  R_R6,
  R_R7,
  R_PC,
  R_COND,
  R_COUNT 
};

enum {
  FL_POS = 1 << 0,
  FL_ZRO = 1 << 1,
  FL_NEG = 1 << 2,
};


enum {
  OP_BR = 0,
  OP_ADD,
  OP_LD,
  OP_ST,
  OP_JSR,
  OP_AND,
  OP_LDR,
  OP_STR,
  OP_RTI,
  OP_NOT,
  OP_LDI,
  OP_STI,
  OP_JMP,
  OP_RES,
  OP_LEA,
  OP_TRAP 
};

uint16_t memory[MAX_MEMORY];
uint16_t reg[R_COUNT];

uint16_t mem_read(uint16_t address){
  return memory[address];
}


int main(int argc, const char* argv[]){
  reg[R_COND] = FL_ZRO;

  enum { PC_START = 0x3000};
  reg[R_PC] = PC_START;

  int running = 1;
  while(running){
    uint16_t instr = mem_read(reg[R_PC]++);
    uint16_t op = instr >> 12;

    switch(op){
      case OP_ADD:
        break;
      case OP_AND:
        break;
      case OP_NOT:
        break;
      case OP_BR:
        break;
      case OP_JMP:
        break;
      case OP_JSR:
        break;
      case OP_LD:
        break;
      case OP_LDI:
        break;
      case OP_LDR:
        break;
      case OP_LEA:
        break;
      case OP_ST:
        break;
      case OP_STR:
        break;
      case OP_STI:
        break;
      case OP_TRAP:
        break;

      case OP_RES:
      case OP_RTI:
      default:
        /*bad opcode thingi here */
        break;
    }




  }
}
