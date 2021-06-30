#ifndef INCLUDED_INSTRUCTION_H
#define INCLUDED_INSTRUCTION_H

#include<stdint.h>

#include "cpu.h"

#define I_ADD               0b00000000000100
#define I_SUB               0b00000000001000

#define I_LOAD_WORD         0b00000001000000
#define I_STORE_WORD        0b00000001000100

#define I_NOP               0b00000000000000
#define I_SHUTDOWN          0b11110000000000
#define I_DEBUG             0b11110000000100

#define INST_MASK           0b11111111111100

Word ins_1reg(uint64_t opecode, uint64_t reg1);
Word ins_2reg(uint64_t opecode, uint64_t dest, uint64_t reg1);
Word ins_3reg(uint64_t opecode, uint64_t dest, uint64_t reg1, uint64_t reg2);
Word ins_2regi(uint64_t opecode, uint64_t dest, uint64_t reg1, uint64_t imm);
Word ins_3regi(uint64_t opecode, uint64_t dest, uint64_t reg1, uint64_t reg2, uint64_t imm);
Word ins_no_arg(uint64_t opecode);
Word ins_2regfi(uint64_t opecode, uint64_t func, uint64_t dest, uint64_t reg1, uint64_t imm);

#endif
