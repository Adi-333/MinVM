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
uint16_t sign_extnd(uint16_t x, int bit_count){
  if ((x >> (bit_count - 1)) & 1) {
    x |= (0xFFFF << bit_count);
  }
  return x;
}


void update_flags(uint16_t r){
  if(reg[r] == 0){
    reg[R_COND] = FL_ZRO;
  }
  else if(reg[r] >> 15){
    reg[R_COND] = FL_NEG;
  }
  else{
    reg[R_COND] = FL_POS;
  }
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
      case OP_ADD:{
        uint16_t DR = ((instr >> 9) & 0x7);
        uint16_t SR1 = ((instr >> 6) & 0x7);
        uint16_t imm_flag = ((instr >> 5) & 0x1);

        if(!imm_flag){
          uint16_t SR2 = (instr & 0x7);
          reg[DR] = reg[SR1] + reg[SR2];
        }
        else{
          uint16_t imm5 = sign_extnd((instr & 0x001F), 5);
          // in the above line we're masking the last 5 bits to get the imm5
          // and then extending the recieved 5 bit number to 16 bits for calculations ahead;
          
          reg[DR] = reg[SR1] + imm5;
        }

        update_flags(DR);

        break;
      }
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
