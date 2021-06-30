#ifndef INCLUDED_INSTRUCTION_H
#define INCLUDED_INSTRUCTION_H

#include<stdint.h>

#include "cpu.h"

#define I_ADD               0b00000000000100
#define I_SUB               0b00000000001000
#define I_MUL_ADD           0b00000000001100
#define I_DIV_ADD           0b00000000010000

#define I_LOAD_WORD         0b00000001000000
#define I_STORE_WORD        0b00000001000100

#define I_JUMP              0b00000010000000

#define I_NOP               0b00000000000000
#define I_SHUTDOWN          0b11110000000000
#define I_DEBUG             0b11110000000100

#define INST_MASK           0b11111111111100

Word from_raw(const uint64_t raw);
Word ins_a(const uint64_t opecode, const uint64_t a);
Word ins_di(const uint64_t opecode, const uint64_t dest, const uint64_t imm);
Word ins_da(const uint64_t opecode, const uint64_t dest, const uint64_t a);
Word ins_dab(const uint64_t opecode, const uint64_t dest, const uint64_t reg1, const uint64_t reg2);
Word ins_dai(const uint64_t opecode, const uint64_t dest, const uint64_t reg1, const uint64_t imm);
Word ins_dabi(const uint64_t opecode, const uint64_t dest, const uint64_t reg1, const uint64_t reg2, const uint64_t imm);
Word ins_fdai(const uint64_t opecode, const uint64_t func, const uint64_t dest, const uint64_t reg1, const uint64_t imm);
Word ins_none(const uint64_t opecode);
Word ins_fabi(const uint64_t opecode, const uint64_t func, const uint64_t a, const uint64_t b, const uint64_t imm);

#endif
